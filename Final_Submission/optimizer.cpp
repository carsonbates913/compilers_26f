#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <llvm-c/Core.h>
#include <llvm-c/Types.h>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <vector>
#include "optimizer.h"

static std::unordered_map<LLVMBasicBlockRef, std::set<LLVMValueRef>> genSets;
static std::unordered_map<LLVMBasicBlockRef, std::set<LLVMValueRef>> killSets;
static std::set<LLVMValueRef> totalStoreSet;
static std::unordered_map<LLVMBasicBlockRef, std::set<LLVMValueRef>> inSets;
static std::unordered_map<LLVMBasicBlockRef, std::set<LLVMValueRef>> outSets;

static std::unordered_map<LLVMBasicBlockRef, std::set<LLVMBasicBlockRef>> predecessors;
static std::set<LLVMValueRef> r;

static std::set<LLVMValueRef> marked;

static bool localOnly = false;

static bool constantFolding(LLVMValueRef function);
static bool constantPropagation(LLVMValueRef function);
static bool deadCode(LLVMValueRef function);
static bool commonSubexpressions(LLVMValueRef function);


static LLVMValueRef getCnstFold(LLVMValueRef instruction, LLVMOpcode op, LLVMValueRef LHS, LLVMValueRef RHS){
	LLVMBuilderRef x = LLVMCreateBuilder();
	LLVMPositionBuilderBefore(x,instruction);
	LLVMValueRef foldcnst = NULL;
	switch (op){
		case LLVMAdd:
			foldcnst = LLVMBuildAdd(x, LHS, RHS, "sum");
			break;
		case LLVMMul:
			foldcnst = LLVMBuildMul(x, LHS, RHS, "product");
			break;
		case LLVMSub:
			foldcnst = LLVMBuildSub(x, LHS, RHS, "sub");
			break;
		default:
			break;
	}
	LLVMDisposeBuilder(x);
	return foldcnst;
}

static bool sameOps(LLVMValueRef first, LLVMValueRef second){
	LLVMOpcode firstOp = LLVMGetInstructionOpcode(first);
	LLVMOpcode secondOp = LLVMGetInstructionOpcode(second);
	if(firstOp != secondOp){
		return false;
	}
	LLVMValueRef firstLHS = LLVMGetOperand(first, 0);
	LLVMValueRef secondLHS = LLVMGetOperand(second, 0);
	if(firstLHS != secondLHS){
		return false;
	}

	LLVMValueRef firstRHS = LLVMGetOperand(first, 1);
	LLVMValueRef secondRHS = LLVMGetOperand(second, 1);
	if(firstRHS != secondRHS){
		return false;
	}
	return true;
}

static bool constantFolding(LLVMValueRef function){

	bool isChanged = false;

	for (LLVMBasicBlockRef basicBlock = LLVMGetFirstBasicBlock(function); basicBlock; basicBlock = LLVMGetNextBasicBlock(basicBlock)) {
		for (LLVMValueRef instruction = LLVMGetFirstInstruction(basicBlock); instruction; instruction = LLVMGetNextInstruction(instruction)) {

			LLVMOpcode op = LLVMGetInstructionOpcode(instruction);

			//constant folding
			if (op == LLVMAdd || op == LLVMMul || op == LLVMSub){
				//Checking if both of the operands are constants
				LLVMValueRef LHS = LLVMGetOperand(instruction, 0);
				LLVMValueRef RHS = LLVMGetOperand(instruction, 1);
				if (LLVMIsAConstantInt(LHS) && LLVMIsAConstantInt(RHS) && LLVMGetFirstUse(instruction) != NULL) {
					LLVMValueRef foldcnst = getCnstFold(instruction, op, LHS, RHS);
					LLVMReplaceAllUsesWith(instruction, foldcnst);
					isChanged = true;
				}
			}
		}
	}

	return isChanged;
}

static bool constantPropagation(LLVMValueRef function){

	bool isChanged = false;

	genSets.clear();
	killSets.clear();
	totalStoreSet.clear();
	inSets.clear();
	outSets.clear();
	predecessors.clear();
	r.clear();
	marked.clear();

	for (
		LLVMBasicBlockRef basicBlock = LLVMGetFirstBasicBlock(function);
		basicBlock;
		basicBlock = LLVMGetNextBasicBlock(basicBlock)
	) {
		LLVMValueRef term = LLVMGetBasicBlockTerminator(basicBlock);
		unsigned int numSuccessors = LLVMGetNumSuccessors(term);
		for(int i = 0; i < numSuccessors; i ++){
			LLVMBasicBlockRef successor = LLVMGetSuccessor(term, i);
			if (!predecessors[successor].contains(basicBlock)){
				predecessors[successor].insert(basicBlock);
			}
		}
	}

	for (
		LLVMBasicBlockRef basicBlock = LLVMGetFirstBasicBlock(function);
		basicBlock;
		basicBlock = LLVMGetNextBasicBlock(basicBlock)
	) {
		for (LLVMValueRef instruction = LLVMGetFirstInstruction(basicBlock); instruction;
		instruction = LLVMGetNextInstruction(instruction)) {
			if (LLVMGetInstructionOpcode(instruction) == LLVMStore){
				totalStoreSet.insert(instruction);
			}
		}
	}


	for (
		LLVMBasicBlockRef basicBlock = LLVMGetFirstBasicBlock(function);
		basicBlock;
		basicBlock = LLVMGetNextBasicBlock(basicBlock)
	) {

		for (
			LLVMValueRef instruction = LLVMGetFirstInstruction(basicBlock);
			instruction;
			instruction = LLVMGetNextInstruction(instruction)
		) {
	
			LLVMOpcode op = LLVMGetInstructionOpcode(instruction);

			if ( op == LLVMStore ){
				LLVMValueRef destination = LLVMGetOperand(instruction, 1);
				//used AI to learn how to do this single erasure method
				std::erase_if(genSets[basicBlock], [&](LLVMValueRef s) { return LLVMGetOperand(s, 1) == destination; });
				genSets[basicBlock].insert(instruction);
			}

			if ( op == LLVMStore ) {
				LLVMValueRef destination = LLVMGetOperand(instruction, 1);
				for ( LLVMValueRef curr_instruction : totalStoreSet){
					LLVMValueRef currDestination = LLVMGetOperand(curr_instruction, 1);
					if (currDestination == destination && curr_instruction != instruction && !killSets[basicBlock].contains(curr_instruction)){
						killSets[basicBlock].insert(curr_instruction);
					}
				}
			}
		}
	}

	for (
		LLVMBasicBlockRef basicBlock = LLVMGetFirstBasicBlock(function);
		basicBlock;
		basicBlock = LLVMGetNextBasicBlock(basicBlock)
	) {
		outSets[basicBlock] = genSets[basicBlock];
	}

	bool setsChanged = true;

	while(setsChanged){

		setsChanged = false;

		for (
			LLVMBasicBlockRef basicBlock = LLVMGetFirstBasicBlock(function);
			basicBlock;
			basicBlock = LLVMGetNextBasicBlock(basicBlock)
		) {

			std::set<LLVMValueRef> newInSet;
			for(LLVMBasicBlockRef pred : predecessors[basicBlock]){
				for(LLVMValueRef x : outSets[pred]){
					newInSet.insert(x);
				}
			}

			inSets[basicBlock] = newInSet;


			std::set<LLVMValueRef> oldOutSet = outSets[basicBlock];

			std::set<LLVMValueRef> newOutSet;

			newOutSet = newInSet;

			for(LLVMValueRef x : killSets[basicBlock]){
				newOutSet.erase(x);
			}


			for(LLVMValueRef x : genSets[basicBlock]){
				newOutSet.insert(x);
			}

			outSets[basicBlock] = newOutSet;

			if(outSets[basicBlock] != oldOutSet){
				setsChanged = true;
			}
		}

	}

	//Final alterations
	for (
		LLVMBasicBlockRef basicBlock = LLVMGetFirstBasicBlock(function);
		basicBlock;
		basicBlock = LLVMGetNextBasicBlock(basicBlock)
	) {
		r = inSets[basicBlock];
		for (
			LLVMValueRef instruction = LLVMGetFirstInstruction(basicBlock);
			instruction;
			instruction = LLVMGetNextInstruction(instruction)
		) {
			LLVMOpcode op = LLVMGetInstructionOpcode(instruction);
			if (op == LLVMStore){
				LLVMValueRef destination = LLVMGetOperand(instruction, 1);

				//1. remove stores killed
				std::erase_if(r, [&](LLVMValueRef s) { return LLVMGetOperand(s, 1) == destination; });

				//2. add this store
				r.insert(instruction);
			}
			if (op == LLVMLoad){
				LLVMValueRef address = LLVMGetOperand(instruction, 0);
				//find all instructions in r that store to that address
				std::set<LLVMValueRef> r_address_match;

				for(LLVMValueRef curr_instruction : r){
					LLVMValueRef currDestination = LLVMGetOperand(curr_instruction, 1);
					if(currDestination == address){
						r_address_match.insert(curr_instruction);
					}
				}

				if(!r_address_match.empty()){

					bool allGood = true;

					//constant to match
					LLVMValueRef constant = NULL;

					for(LLVMValueRef curr_instruction : r_address_match){
						LLVMValueRef operand = LLVMGetOperand(curr_instruction, 0);
						if(!LLVMIsAConstantInt(operand)){
							allGood = false;
							break;
						}
						if(constant == NULL){
							constant = operand;
						}else if(LLVMConstIntGetSExtValue(operand) !=
						LLVMConstIntGetSExtValue(constant)){
							allGood = false;
							break;
						}

					}

					if(allGood){
						LLVMReplaceAllUsesWith(instruction, constant);
						marked.insert(instruction);
					}
				}
			}
		}
	}

	for(LLVMValueRef load : marked){
		LLVMInstructionEraseFromParent(load);
		isChanged = true;
	}
	marked.clear();

	return isChanged;
}

static bool deadCode(LLVMValueRef function){

	bool isChanged = false;

	for (
		LLVMBasicBlockRef basicBlock = LLVMGetFirstBasicBlock(function);
		basicBlock;
		basicBlock = LLVMGetNextBasicBlock(basicBlock)
	){
			
		std::vector<LLVMValueRef> toDelete;

		for (
			LLVMValueRef instruction = LLVMGetFirstInstruction(basicBlock);
			instruction;
			instruction = LLVMGetNextInstruction(instruction)
		) {
			LLVMOpcode op = LLVMGetInstructionOpcode(instruction);
			if (!(op == LLVMStore || op == LLVMAlloca || op == LLVMCall || LLVMIsATerminatorInst(instruction) != NULL) && LLVMGetFirstUse(instruction) == NULL)
					toDelete.push_back(instruction);
		}
		for (LLVMValueRef inst : toDelete)
				LLVMInstructionEraseFromParent(inst);

		isChanged = (isChanged || !toDelete.empty());

	}
	return isChanged;
}

static bool commonSubexpressions(LLVMValueRef function){

	bool isChanged = false;

	for (
		LLVMBasicBlockRef basicBlock = LLVMGetFirstBasicBlock(function);
		basicBlock;
		basicBlock = LLVMGetNextBasicBlock(basicBlock)
	) {

		for (
			LLVMValueRef instruction = LLVMGetFirstInstruction(basicBlock);
			instruction;
			instruction = LLVMGetNextInstruction(instruction)
		) {

			LLVMOpcode op = LLVMGetInstructionOpcode(instruction);

			if(op == LLVMAdd || op == LLVMMul || op == LLVMSub){
				for (LLVMValueRef u = LLVMGetNextInstruction(instruction);u;u = LLVMGetNextInstruction(u)){
					if(sameOps(instruction, u)){
						LLVMReplaceAllUsesWith(u, instruction);
						isChanged = true;
					}
				}
			}

			if (op == LLVMLoad){
				LLVMValueRef address = LLVMGetOperand(instruction, 0);
				for (LLVMValueRef u = LLVMGetNextInstruction(instruction);u;u = LLVMGetNextInstruction(u)){
					LLVMOpcode u_opcode = LLVMGetInstructionOpcode(u);
					if((u_opcode == LLVMStore && LLVMGetOperand(u, 1) == address)){
						break;
					}
					if (u_opcode == LLVMLoad) {
						LLVMValueRef u_address = LLVMGetOperand(u, 0);
						if (address == u_address) {
								LLVMReplaceAllUsesWith(u, instruction);
								isChanged = true;
						}
					}
				}
			}
 		}
	}
	return isChanged;
}

static void optimizeLoop(LLVMValueRef function){

	if(localOnly){
		constantFolding(function);
		commonSubexpressions(function);
		bool isChanged = true;
		while(isChanged){
			isChanged = deadCode(function);
		};
		
	}else{
		bool isChanged = true;

		while(isChanged){
			bool a = constantPropagation(function);
			bool b = constantFolding(function);
			bool c = commonSubexpressions(function);
			bool d = deadCode(function);
			isChanged = (a || b || c || d);
		}
	}

}

void optimize(LLVMModuleRef module, bool local_only){
	localOnly = local_only;
	for (
		LLVMValueRef function =  LLVMGetFirstFunction(module); 
		function; 
		function = LLVMGetNextFunction(function)
	) {
		optimizeLoop(function);
 	}
}