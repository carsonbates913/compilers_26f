#include <stdio.h>
#include <llvm-c/Core.h>
#include <algorithm>
#include <map>
#include <set>
#include <string>
#include <tuple>
#include <vector>
#include "assembly_generator.h"

std::map<LLVMValueRef, std::string> reg_map;

void compute_liveness(
  LLVMBasicBlockRef basicblock,
  std::map<LLVMValueRef, int>& inst_index,
  std::map<LLVMValueRef, std::tuple<int, int>>& live_range,
  std::map<LLVMValueRef, int>& num_calls,
  std::vector<LLVMValueRef>& num_calls_list,
  std::map<LLVMValueRef, int>& liveness,
  std::vector<LLVMValueRef>& liveness_list
){
  
	for (
    LLVMValueRef instruction = LLVMGetFirstInstruction(basicblock); 
    instruction;
    instruction = LLVMGetNextInstruction(instruction)) 
  {
    LLVMOpcode op = LLVMGetInstructionOpcode(instruction);

    if(op != LLVMAlloca){

      int index = inst_index.at(instruction);

      liveness[instruction] = 0;
      num_calls[instruction] = 0;
      liveness_list.push_back(instruction);
      num_calls_list.push_back(instruction);

      live_range[instruction] = std::make_tuple(index, index);

      for(
        LLVMUseRef u = LLVMGetFirstUse(instruction);
        u;
        u = LLVMGetNextUse(u)
      ){
        LLVMValueRef user = LLVMGetUser(u);
        int newIndex = inst_index.at(user);
        num_calls[instruction] = num_calls[instruction] + 1;
        auto& [start, end] = live_range.at(instruction);
        end = std::max(end, newIndex);
        liveness[instruction] = end - start;
      }
    }
  }

  std::sort(liveness_list.begin(), liveness_list.end(), [&](const LLVMValueRef& a, const LLVMValueRef& b) {
        return liveness.at(a) > liveness.at(b);
    });

  std::sort(num_calls_list.begin(), num_calls_list.end(), [&](const LLVMValueRef& a, const LLVMValueRef& b) {
        return num_calls.at(a) > num_calls.at(b);
    });

}

LLVMValueRef find_spill(
  LLVMValueRef instr, 
  std::map<LLVMValueRef, std::string>& reg_map, 
  std::map<LLVMValueRef, int>& inst_index, 
  std::vector<LLVMValueRef>& sorted_list, 
  std::map<LLVMValueRef, std::tuple<int, int>>& live_range
){
  int index = inst_index[instr];

  for(int i = 0; i < sorted_list.size(); i++){
    LLVMValueRef val = sorted_list.at(i);
    auto& [start, end] = live_range.at(val);
    if((index >= start && index <= end) && (reg_map.contains(val)) && (reg_map.at(val) != "-1")){
      return val;
    }
  }
  return NULL;
}

void register_allocation(LLVMValueRef function){
	for (
    LLVMBasicBlockRef basicBlock = LLVMGetFirstBasicBlock(function);
    basicBlock;
    basicBlock = LLVMGetNextBasicBlock(basicBlock)
  ){
    std::set<std::string> available_registers = {"ebx", "ecx", "edx"};

    std::map<LLVMValueRef, int> inst_index;

    int index = 0;

    for (
      LLVMValueRef instruction = LLVMGetFirstInstruction(basicBlock); 
      instruction;
      instruction = LLVMGetNextInstruction(instruction)) 
    {
      LLVMOpcode op = LLVMGetInstructionOpcode(instruction);

      if(op != LLVMAlloca){
        inst_index[instruction] = index;
        index++;
      }
    }

    std::map<LLVMValueRef, std::tuple<int, int>> live_range;
    std::map<LLVMValueRef, int> num_calls;
    std::vector<LLVMValueRef> num_calls_list;
    std::map<LLVMValueRef, int> liveness;
    std::vector<LLVMValueRef> liveness_list;

    compute_liveness(basicBlock, inst_index, live_range, num_calls, num_calls_list, liveness, liveness_list);

    for(
      LLVMValueRef instruction = LLVMGetFirstInstruction(basicBlock);
      instruction;
      instruction = LLVMGetNextInstruction(instruction)
    ){
      LLVMOpcode op = LLVMGetInstructionOpcode(instruction);
      int num_operands = LLVMGetNumOperands(instruction);
      LLVMValueRef firstOperand = nullptr;
      LLVMValueRef secondOperand = nullptr;
      
      if(num_operands > 0){
        firstOperand = LLVMGetOperand(instruction, 0);
      }

      if(num_operands > 1){
        secondOperand = LLVMGetOperand(instruction, 1);
      }

      if(op == LLVMAlloca){
        continue;
      }

      int current_index = inst_index.at(instruction);

      if(op == LLVMStore || op == LLVMBr || ((op == LLVMCall) && (LLVMGetTypeKind(LLVMTypeOf(instruction)) == LLVMVoidTypeKind))){
        for(int i = 0; i < num_operands; i++){
          LLVMValueRef x = LLVMGetOperand(instruction, i);
          if(live_range.contains(x)){
            auto& [start, end] = live_range.at(x);
            if(reg_map.contains(x) && (reg_map.at(x) != "-1") && (end == current_index)){
              available_registers.insert(reg_map.at(x));
            }
          }
        }
        continue;
      }

      bool firstCondition = false;

      bool isArithmatic = (op == LLVMAdd || op == LLVMMul || op == LLVMSub);
      bool firstOperandRegister = (firstOperand && reg_map.contains(firstOperand) && reg_map.at(firstOperand) != "-1");

      if(isArithmatic && firstOperandRegister){
        if(live_range.contains(firstOperand)){
          auto& [start, end] = live_range.at(firstOperand);
          if(end == current_index){
            firstCondition = true;
          }
        }
      }

      if(firstCondition){
        reg_map[instruction] = reg_map.at(firstOperand);

        if(live_range.contains(secondOperand)){
          auto& [start, end] = live_range.at(secondOperand);
          bool isEnding = (end == current_index);
          if(isEnding && reg_map.contains(secondOperand) && reg_map.at(secondOperand) != "-1"){
            available_registers.insert(reg_map.at(secondOperand));
          }
        }
      }else if(available_registers.size() > 0){
        if(available_registers.contains("ebx")){
          reg_map[instruction] = "ebx";
          available_registers.erase("ebx");
        }else if(available_registers.contains("ecx")){
          reg_map[instruction] = "ecx";
          available_registers.erase("ecx");
        }else if(available_registers.contains("edx")){
          reg_map[instruction] = "edx";
          available_registers.erase("edx");
        }

        for(int i = 0; i < num_operands; i++){
          LLVMValueRef x = LLVMGetOperand(instruction, i);
          if(live_range.contains(x)){
            auto& [start, end] = live_range.at(x);
            if(reg_map.contains(x) && (reg_map.at(x) != "-1") && (end == current_index)){
              available_registers.insert(reg_map.at(x));
            }
          }
        }
      }else if (available_registers.size() < 1){
        LLVMValueRef spilled_value = find_spill(instruction, reg_map, inst_index, num_calls_list, live_range);

        if((spilled_value == NULL) || num_calls[spilled_value] > num_calls[instruction]){
          reg_map[instruction] = "-1";
        }else{
          std::string reg = reg_map[spilled_value];
          reg_map[instruction] = reg;
          reg_map[spilled_value] = "-1";
        }

        for(int i = 0; i < num_operands; i++){
          LLVMValueRef x = LLVMGetOperand(instruction, i);
          if(live_range.contains(x)){
            auto& [start, end] = live_range.at(x);
            if(reg_map.contains(x) && (reg_map.at(x) != "-1") && (end == current_index)){
              available_registers.insert(reg_map.at(x));
            }
          }
        }

      }

    }

	}
}


std::pair<std::map<LLVMValueRef, int>, int> get_offset_map(LLVMModuleRef mod){

  std::map<LLVMValueRef, int> offset_map;

  int localMem = 4;

  for (
    LLVMValueRef function =  LLVMGetFirstFunction(mod); 
		function; 
		function = LLVMGetNextFunction(function)
  ){

    if (LLVMCountBasicBlocks(function) == 0) continue;

    int num_params = LLVMCountParams(function);

    LLVMValueRef param = nullptr;

    if(num_params > 0){
      param = LLVMGetParam(function, 0);
      localMem = localMem + 4;
      offset_map[param] = localMem;
    }

    for (
      LLVMBasicBlockRef basicBlock = LLVMGetFirstBasicBlock(function);
      basicBlock; 
      basicBlock = LLVMGetNextBasicBlock(basicBlock)
    ){
      for (
        LLVMValueRef instruction = LLVMGetFirstInstruction(basicBlock); instruction;
  			instruction = LLVMGetNextInstruction(instruction)
      ){
        LLVMOpcode op = LLVMGetInstructionOpcode(instruction);

        if(op == LLVMAlloca){
          localMem = localMem + 4;
          offset_map[instruction] = (-1 * localMem);
        }
        if(op == LLVMStore){
          LLVMValueRef firstOperand = LLVMGetOperand(instruction, 0);
          LLVMValueRef secondOperand = LLVMGetOperand(instruction, 1);
          if(firstOperand == param){
            int x = offset_map[firstOperand];
            offset_map[secondOperand] = x;
          }else if(!LLVMIsConstant(firstOperand)){
            int x = offset_map[secondOperand];
            offset_map[firstOperand] = x;
          }
        }

        if(op == LLVMLoad){
          LLVMValueRef firstOperand = LLVMGetOperand(instruction, 0);
          int x = offset_map[firstOperand];
          offset_map[instruction] = x;
        }
	    } 
 	  }
  }
  return {offset_map, localMem};
}

std::map<LLVMBasicBlockRef, std::string> createBBLabels(LLVMValueRef function){
  std::map<LLVMBasicBlockRef, std::string> bb_labels;
  int index = 0;
  for (
    LLVMBasicBlockRef basicBlock = LLVMGetFirstBasicBlock(function);
    basicBlock; 
    basicBlock = LLVMGetNextBasicBlock(basicBlock)
  ){
    if (LLVMCountBasicBlocks(function) == 0) continue;
    std::string prefix = "bb_label_";
    std::string new_name = prefix + std::to_string(index);
    bb_labels[basicBlock] = new_name;
    index = index + 1;
  }
  return bb_labels;
}

void printDirectives(FILE* outFile, std::string name){
  fprintf(outFile, "\t.text\n");
  fprintf(outFile,"\t.globl \t %s\n", name.c_str());
  fprintf(outFile, "\t.type %s ,@function\n", name.c_str());
  fprintf(outFile, "%s:\n", name.c_str());
}

void printFunctionEnd(FILE* outFile, std::string name){
  fprintf(outFile, "\tleave\n");
  fprintf(outFile, "\tretl\n");
  fprintf(outFile, ".%s_end:\n", name.c_str());
}

void code_generation(LLVMModuleRef mod, std::string outFileName){
  FILE* outFile = fopen(outFileName.c_str(), "w");
  if(!outFile){
    fprintf(stderr, "Could not open %s\n", outFileName.c_str());
    return;
  }

  for (
    LLVMValueRef function =  LLVMGetFirstFunction(mod); 
		function; 
		function = LLVMGetNextFunction(function)
  ){
    if (LLVMCountBasicBlocks(function) == 0) continue;
    LLVMValueRef param = nullptr;
    int num_params = LLVMCountParams(function);
    if(num_params > 0){
      param = LLVMGetParam(function, 0);
    }

    size_t len = 0;
    const char* namePtr = LLVMGetValueName2(function, &len);
    std::string funcName(namePtr, len);

    register_allocation(function);
    std::map<LLVMBasicBlockRef, std::string> bb_labels = createBBLabels(function);
    printDirectives(outFile, funcName);

    auto [offset_map, localMem] = get_offset_map(mod);

    fprintf(outFile, "pushl %%ebp\n");
    fprintf(outFile, "movl %%esp, %%ebp\n");
    fprintf(outFile, "subl $%d, %%esp\n", localMem);
    fprintf(outFile, "pushl %%ebx\n");

    for (
      LLVMBasicBlockRef basicBlock = LLVMGetFirstBasicBlock(function);
      basicBlock;
      basicBlock = LLVMGetNextBasicBlock(basicBlock)
    ) {
      fprintf(outFile, "%s:\n", bb_labels[basicBlock].c_str());
      for (
        LLVMValueRef instruction = LLVMGetFirstInstruction(basicBlock);
        instruction;
        instruction = LLVMGetNextInstruction(instruction)
      ) {
        LLVMOpcode op = LLVMGetInstructionOpcode(instruction);

        if(op == LLVMRet){
          LLVMValueRef firstOperand = LLVMGetOperand(instruction, 0);
          if(LLVMIsConstant(firstOperand)){
            fprintf(outFile, "movl $%d, %%eax\n", (int)LLVMConstIntGetSExtValue(firstOperand));
          }else if(reg_map.contains(firstOperand) && reg_map.at(firstOperand) == "-1"){
            int offset = offset_map[firstOperand];
            fprintf(outFile, "movl %d(%%ebp), %%eax\n", offset);
          }else if(reg_map.contains(firstOperand) && reg_map.at(firstOperand) != "-1"){
            std::string reg = reg_map.at(firstOperand);
            fprintf(outFile, "movl %%%s, %%eax\n", reg.c_str());
          }
          fprintf(outFile, "popl %%ebx\n");
          printFunctionEnd(outFile, funcName);
        }
        if(op == LLVMLoad){
          LLVMValueRef firstOperand = LLVMGetOperand(instruction, 0);
          if(reg_map.contains(instruction) && reg_map.at(instruction) != "-1"){
            std::string reg = reg_map.at(instruction);
            if(offset_map.contains(firstOperand)){
              int offset = offset_map.at(firstOperand);
              fprintf(outFile, "movl %d(%%ebp),%%%s\n", offset,reg.c_str());
            }
          }
        }
        if(op == LLVMStore){
          LLVMValueRef firstOperand = LLVMGetOperand(instruction, 0);
          LLVMValueRef secondOperand = LLVMGetOperand(instruction, 1);
          if(firstOperand == param){
            continue;
          }
          if(LLVMIsConstant(firstOperand) && offset_map.contains(secondOperand)){
            int offset = offset_map.at(secondOperand);
            fprintf(outFile, "movl $%d, %d(%%ebp)\n", (int)LLVMConstIntGetSExtValue(firstOperand), offset);
          }
          if(reg_map.contains(firstOperand) && reg_map.at(firstOperand) != "-1"){
            std::string reg = reg_map.at(firstOperand);
            if(offset_map.contains(secondOperand)){
              int offset = offset_map.at(secondOperand);
              fprintf(outFile, "movl %%%s, %d(%%ebp)\n", reg.c_str(), offset);
            }
          }
          if(reg_map.contains(firstOperand) && reg_map.at(firstOperand) == "-1"){
            if(offset_map.contains(firstOperand) && offset_map.contains(secondOperand)){
              int offset1 = offset_map.at(firstOperand);
              fprintf(outFile, "movl %d(%%ebp), %%eax\n", offset1);
              int offset2 = offset_map.at(secondOperand);
              fprintf(outFile, "movl %%eax, %d(%%ebp)\n", offset2);
            }
          }
        }
        if(op == LLVMCall){
          fprintf(outFile, "pushl %%ecx\n");
          fprintf(outFile, "pushl %%edx\n");
          if(LLVMGetNumArgOperands(instruction) > 0){
            LLVMValueRef firstParam = LLVMGetArgOperand(instruction, 0);
            if(LLVMIsConstant(firstParam)){
              fprintf(outFile, "pushl $%d\n", (int)LLVMConstIntGetSExtValue(firstParam));
            }else if(reg_map.contains(firstParam)){
              if(reg_map.at(firstParam) != "-1"){
                std::string reg = reg_map.at(firstParam);
                fprintf(outFile, "pushl %%%s\n", reg.c_str());
              }else{
                if(offset_map.contains(firstParam)){
                  int offset = offset_map.at(firstParam);
                  fprintf(outFile, "pushl %d(%%ebp)\n", offset);
                }
              }
            }
          }
          size_t len = 0;
          const char* namePtr = LLVMGetValueName2(LLVMGetCalledValue(instruction), &len);
          std::string fun(namePtr, len);
          fprintf(outFile, "call %s\n", fun.c_str());
          if(LLVMGetNumArgOperands(instruction) > 0){
            fprintf(outFile, "addl $4, %%esp\n");
          }
          fprintf(outFile, "popl %%edx\n");
          fprintf(outFile, "popl %%ecx\n");
          if(LLVMGetTypeKind(LLVMTypeOf(instruction)) != LLVMVoidTypeKind){
            if(reg_map.contains(instruction)){
              if(reg_map.at(instruction) != "-1"){
                std::string reg = reg_map.at(instruction);
                fprintf(outFile, "movl %%eax, %%%s\n", reg.c_str());
              }else{
                if(offset_map.contains(instruction)){
                  int offset = offset_map.at(instruction);
                  fprintf(outFile, "movl %%eax, %d(%%ebp)\n", offset);
                }
              }
            }
          }
        }
        if(op == LLVMBr){
          if(!LLVMIsConditional(instruction)){
            LLVMValueRef firstOperand = LLVMGetOperand(instruction, 0);
            std::string label = bb_labels.at(LLVMValueAsBasicBlock(firstOperand));
            fprintf(outFile, "jmp %s\n", label.c_str());
          }else{
            LLVMValueRef firstOperand = LLVMGetOperand(instruction, 0);
            LLVMValueRef secondOperand = LLVMGetOperand(instruction, 1);
            LLVMValueRef thirdOperand = LLVMGetOperand(instruction, 2);
            std::string label1 = bb_labels.at(LLVMValueAsBasicBlock(thirdOperand));
            std::string label2 = bb_labels.at(LLVMValueAsBasicBlock(secondOperand));
            LLVMIntPredicate pred = LLVMGetICmpPredicate(firstOperand);
            std::string jxx;

            switch (pred) {
                case LLVMIntEQ:  jxx = "je";  break;
                case LLVMIntNE:  jxx = "jne"; break;
                case LLVMIntSLT: jxx = "jl";  break;
                case LLVMIntSGT: jxx = "jg";  break;
                case LLVMIntSLE: jxx = "jle"; break;
                case LLVMIntSGE: jxx = "jge"; break;
                default: break;
            }
            fprintf(outFile, "%s %s\n", jxx.c_str(), label1.c_str());
            fprintf(outFile, "jmp %s\n", label2.c_str());
          }

        }
        if(op == LLVMAdd || op == LLVMMul || op == LLVMSub){
          LLVMValueRef firstOperand = LLVMGetOperand(instruction, 0);
          LLVMValueRef secondOperand = LLVMGetOperand(instruction, 1);
          std::string reg;
          if(reg_map.contains(instruction) && reg_map.at(instruction) != "-1"){
            reg = reg_map.at(instruction);
          }else{
            reg = "eax";
          }
          if(LLVMIsConstant(firstOperand)){
            fprintf(outFile, "movl $%d, %%%s\n", (int)LLVMConstIntGetSExtValue(firstOperand), reg.c_str());
          }else if(reg_map.contains(firstOperand) && reg_map.at(firstOperand) != "-1"){
            std::string regy = reg_map.at(firstOperand);
            if(!(regy == reg)){
              fprintf(outFile, "movl %%%s, %%%s\n", regy.c_str(), reg.c_str());
            }
          }else if (reg_map.contains(firstOperand) && reg_map.at(firstOperand) == "-1"){
            if(offset_map.contains(firstOperand)){
              int offset = offset_map.at(firstOperand);
              fprintf(outFile, "movl %d(%%ebp), %%%s\n", offset, reg.c_str());
            }
          }
          if(LLVMIsConstant(secondOperand)){
            std::string operation;
            if(op == LLVMAdd){
              operation = "addl";
            }else if(op == LLVMMul){
              operation = "imull";
            }else if(op == LLVMSub){
              operation = "subl";
            }
            fprintf(outFile, "%s $%d, %%%s\n", operation.c_str(), (int)LLVMConstIntGetSExtValue(secondOperand), reg.c_str());
          }else if(reg_map.contains(secondOperand) && reg_map.at(secondOperand) != "-1"){
            std::string regz = reg_map.at(secondOperand);
            std::string operation;
            if(op == LLVMAdd){
              operation = "addl";
            }else if(op == LLVMMul){
              operation = "imull";
            }else if(op == LLVMSub){
              operation = "subl";
            }
            fprintf(outFile, "%s %%%s, %%%s\n", operation.c_str(), regz.c_str(), reg.c_str());
          }else if (reg_map.contains(secondOperand) && reg_map.at(secondOperand) == "-1"){
            std::string operation;
            if(op == LLVMAdd){
              operation = "addl";
            }else if(op == LLVMMul){
              operation = "imull";
            }else if(op == LLVMSub){
              operation = "subl";
            }
            if(offset_map.contains(secondOperand)){
              int offset = offset_map.at(secondOperand);
              fprintf(outFile, "%s %d(%%ebp), %%%s\n", operation.c_str(), offset, reg.c_str());
            }
          }
          if(reg_map.contains(instruction) && reg_map.at(instruction) == "-1"){
            if(offset_map.contains(instruction)){
              int offset = offset_map.at(instruction);
              fprintf(outFile, "movl %%eax, %d(%%ebp)\n", offset);
            }
          }

        }
        if(op == LLVMICmp){
          LLVMValueRef firstOperand = LLVMGetOperand(instruction, 0);
          LLVMValueRef secondOperand = LLVMGetOperand(instruction, 1);
          std::string reg;
          if(reg_map.contains(instruction) && reg_map.at(instruction) != "-1"){
            reg = reg_map.at(instruction);
          }else{
            reg = "eax";
          }

          if(LLVMIsConstant(firstOperand)){
            fprintf(outFile, "movl $%d, %%%s\n", (int)LLVMConstIntGetSExtValue(firstOperand), reg.c_str());
          }else if(reg_map.contains(firstOperand) && reg_map.at(firstOperand) != "-1"){
            std::string regy = reg_map.at(firstOperand);
            if(!(regy == reg)){
              fprintf(outFile, "movl %%%s, %%%s\n", regy.c_str(), reg.c_str());
            }
          }else if (reg_map.contains(firstOperand) && reg_map.at(firstOperand) == "-1"){
            if(offset_map.contains(firstOperand)){
              int offset = offset_map.at(firstOperand);
              fprintf(outFile, "movl %d(%%ebp), %%%s\n", offset, reg.c_str());
            }
          }

          if(LLVMIsConstant(secondOperand)){
            fprintf(outFile, "cmpl $%d, %%%s\n", (int)LLVMConstIntGetSExtValue(secondOperand), reg.c_str());
          }else if(reg_map.contains(secondOperand) && reg_map.at(secondOperand) != "-1"){
            std::string regz = reg_map.at(secondOperand);
            fprintf(outFile, "cmpl %%%s, %%%s\n", regz.c_str(), reg.c_str());
          }else if (reg_map.contains(secondOperand) && reg_map.at(secondOperand) == "-1"){
            if(offset_map.contains(secondOperand)){
              int offset = offset_map.at(secondOperand);
              fprintf(outFile, "cmpl %d(%%ebp), %%%s\n", offset, reg.c_str());
            }
          }
        }
      }
    }
  }
  fclose(outFile);
}


/*std::vector<std::string> items = {"apple", "banana", "cherry"};
    std::unordered_map<std::string, int> priority = {
        {"apple", 20},
        {"banana", 50},
        {"cherry", 10}
    };

    // Sort descending by the mapped value
    std::sort(items.begin(), items.end(), [&](const std::string& a, const std::string& b) {
        return priority.at(a) > priority.at(b); // Use '<' for ascending
    });

    // items is now: {"banana", "apple", "cherry"}
    for (const auto& item : items) {
        s*/




              /*
      if(op == LLVMAdd || op == LLVMMul || op == LLVMSub){
        LLVMValueRef LHS = LLVMGetOperand(instruction, 0);
        auto& [start, end] = live_range.at(LHS)
        end = index;
        LLVMValueRef RHS = LLVMGetOperand(instruction, 1);
        auto& [start, end] = live_range.at(RHS)
        end = index;
      }

      if(op == LLVMLoad){
        LLVMValueRef address = LLVMGetOperand(instruction, 0);
        auto& [start, end] = live_range.at(address)
        end = index;
      }

      if (op == LLVMStore){
        LLVMValueRef destination = LLVMGetOperand(instruction, 1);
        auto& [start, end] = live_range.at(destination)
        end = index;
      }

      if (op == LLVMCall){
        int num_args = LLVMGetNumArgOperands(instruction);

        for (int i = 0; i < num_args; i++){
          LLVMGetArgOperand()
        }
      }

      if(op != LLVMStore && LLVMIsATerminatorInst(instruction)){
        live_range[instruction] = std::make_tuple(index, index);
      }
      */