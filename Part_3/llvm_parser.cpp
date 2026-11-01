#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <llvm-c/Core.h>
#include <llvm-c/IRReader.h>
#include <llvm-c/Types.h>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <vector>

#define prt(x) if(x) { printf("%s\n", x); }

static std::unordered_map<LLVMBasicBlockRef, std::set<LLVMValueRef>> genSets;
static std::unordered_map<LLVMBasicBlockRef, std::set<LLVMValueRef>> killSets;
static std::set<LLVMValueRef> totalStoreSet;
static std::unordered_map<LLVMBasicBlockRef, std::set<LLVMValueRef>> inSets;
static std::unordered_map<LLVMBasicBlockRef, std::set<LLVMValueRef>> outSets;

static std::unordered_map<LLVMBasicBlockRef, std::set<LLVMBasicBlockRef>> predecessors;
std::set<LLVMValueRef> r;

std::set<LLVMValueRef> marked;

static bool localOnly = false;

bool constantFolding(LLVMValueRef function);
bool constantPropagation(LLVMValueRef function);
void walkBBInstructionsDeadCode(LLVMBasicBlockRef bb);
void walkBBInstructionsCSE(LLVMBasicBlockRef bb);

/* This function reads the given llvm file and loads the LLVM IR into
	 data-structures that we can works on for optimization phase.
*/



LLVMValueRef getCnstFold(LLVMValueRef instruction, LLVMOpcode op, LLVMValueRef LHS, LLVMValueRef RHS){
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

bool sameOps(LLVMValueRef first, LLVMValueRef second){
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



bool constantFolding(LLVMValueRef function){

	bool changeMade = false;

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
					changeMade = true;
				}
			}
		}
	}

	return changeMade;
}


bool constantPropagation(LLVMValueRef function){

	bool changeMade = false;

	genSets.clear();
	killSets.clear();
	totalStoreSet.clear();
	inSets.clear();
	outSets.clear();
	predecessors.clear();
	r.clear();
	marked.clear();

	//construct predecessors
	for (LLVMBasicBlockRef basicBlock = LLVMGetFirstBasicBlock(function);
	basicBlock; basicBlock = LLVMGetNextBasicBlock(basicBlock)) {
		LLVMValueRef term = LLVMGetBasicBlockTerminator(basicBlock);
		unsigned int numSuccessors = LLVMGetNumSuccessors(term);
		for(int i = 0; i < numSuccessors; i ++){
			LLVMBasicBlockRef successor = LLVMGetSuccessor(term, i);
			if (!predecessors[successor].contains(basicBlock)){
				predecessors[successor].insert(basicBlock);
			}
		}
	}

	//construct total store set 
	for (LLVMBasicBlockRef basicBlock = LLVMGetFirstBasicBlock(function); basicBlock; basicBlock = LLVMGetNextBasicBlock(basicBlock)) {
		for (LLVMValueRef instruction = LLVMGetFirstInstruction(basicBlock); instruction;
		instruction = LLVMGetNextInstruction(instruction)) {
			if (LLVMGetInstructionOpcode(instruction) == LLVMStore){
				totalStoreSet.insert(instruction);
			}
		}
	}

	//initialize gen and kill sets
	for (LLVMBasicBlockRef basicBlock = LLVMGetFirstBasicBlock(function); basicBlock; basicBlock = LLVMGetNextBasicBlock(basicBlock)) {
		LLVMBasicBlockRef bb = basicBlock;

		for (LLVMValueRef instruction = LLVMGetFirstInstruction(bb); instruction;
		instruction = LLVMGetNextInstruction(instruction)) {
	
			// LLVMGetInstructionOpcode gives you LLVMOpcode that is a enum		
			LLVMOpcode op = LLVMGetInstructionOpcode(instruction);

			// Construct Gen Set
			if ( op == LLVMStore ){
				LLVMValueRef destination = LLVMGetOperand(instruction, 1);
				std::erase_if(genSets[bb], [&](LLVMValueRef s) { return LLVMGetOperand(s, 1) == destination; });
				genSets[bb].insert(instruction);
			}
			// Construct Kill Set
			if ( op == LLVMStore ) {
				LLVMValueRef destination = LLVMGetOperand(instruction, 1);
				for ( LLVMValueRef currI : totalStoreSet){
					LLVMValueRef currDestination = LLVMGetOperand(currI, 1);
					if (currDestination == destination && currI != instruction && !killSets[bb].contains(currI)){
						killSets[bb].insert(currI);
					}
				}
			}
		}
	}

	//in and out sets

	for (LLVMBasicBlockRef basicBlock = LLVMGetFirstBasicBlock(function); basicBlock; basicBlock = LLVMGetNextBasicBlock(basicBlock)) {
		outSets[basicBlock] = genSets[basicBlock];
	}

	bool isChanged = true;

	while(isChanged){

		isChanged = false;

		for (LLVMBasicBlockRef basicBlock = LLVMGetFirstBasicBlock(function); basicBlock; basicBlock = LLVMGetNextBasicBlock(basicBlock)) {

			// get the new In Set
			std::set<LLVMValueRef> newInSet;
			for(LLVMBasicBlockRef pred : predecessors[basicBlock]){
				for(LLVMValueRef x : outSets[pred]){
					newInSet.insert(x);
				}
			}

			inSets[basicBlock] = newInSet;

			// establish the old Out Set

			std::set<LLVMValueRef> oldOutSet = outSets[basicBlock];

			//1. set it equal to the newInSet
			std::set<LLVMValueRef> newOutSet;

			newOutSet = newInSet;

			//2. erase the kill set

			for(LLVMValueRef x : killSets[basicBlock]){
				newOutSet.erase(x);
			}

			//3. union with GenSet

			for(LLVMValueRef x : genSets[basicBlock]){
				newOutSet.insert(x);
			}

			//4. update outSets
			outSets[basicBlock] = newOutSet;

			//check equality

			if(outSets[basicBlock] != oldOutSet){
				isChanged = true;
			}
		}

	}

	//Final alterations
	for (LLVMBasicBlockRef basicBlock = LLVMGetFirstBasicBlock(function); basicBlock; basicBlock = LLVMGetNextBasicBlock(basicBlock)) {
		r = inSets[basicBlock];
		for (LLVMValueRef instruction = LLVMGetFirstInstruction(basicBlock); instruction; instruction = LLVMGetNextInstruction(instruction)) {
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

				for(LLVMValueRef currI : r){
					LLVMValueRef currDestination = LLVMGetOperand(currI, 1);
					if(currDestination == address){
						r_address_match.insert(currI);
					}
				}

				if(!r_address_match.empty()){

					bool allGood = true;

					//constant to match
					LLVMValueRef constant = NULL;

					for(LLVMValueRef currI : r_address_match){
						LLVMValueRef operand = LLVMGetOperand(currI, 0);
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
		changeMade = true;
	}
	marked.clear();

	return changeMade;
}

void walkBBInstructionsDeadCode(LLVMBasicBlockRef bb){

	bool isChanged = true;

	while(isChanged){
		std::vector<LLVMValueRef> toDelete;

		for (LLVMValueRef instruction = LLVMGetFirstInstruction(bb);instruction; instruction = LLVMGetNextInstruction(instruction)) {
			LLVMOpcode op = LLVMGetInstructionOpcode(instruction);
			if (!(op == LLVMStore || op == LLVMAlloca || op == LLVMCall || LLVMIsATerminatorInst(instruction) != NULL) && LLVMGetFirstUse(instruction) == NULL)
					toDelete.push_back(instruction);
		}
    for (LLVMValueRef inst : toDelete)
        LLVMInstructionEraseFromParent(inst);

    isChanged = !toDelete.empty();

	}
}


void walkBBInstructionsCSE(LLVMBasicBlockRef bb){
	for (LLVMValueRef instruction = LLVMGetFirstInstruction(bb); instruction;
  				instruction = LLVMGetNextInstruction(instruction)) {
	
		// LLVMGetInstructionOpcode gives you LLVMOpcode that is a enum		
		LLVMOpcode op = LLVMGetInstructionOpcode(instruction);

		//Common Subexpression Elimination

		if(op == LLVMAdd || op == LLVMMul || op == LLVMSub){
			for (LLVMValueRef u = LLVMGetNextInstruction(instruction);u;u = LLVMGetNextInstruction(u)){
				if(sameOps(instruction, u)){
					LLVMReplaceAllUsesWith(u, instruction);
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
					LLVMValueRef u_address = LLVMGetOperand(u, 0);   // a load's address
					if (address == u_address) {
							LLVMReplaceAllUsesWith(u, instruction);
					}
				}
			}
		}
 }
}


 
LLVMModuleRef createLLVMModel(char * filename){
	char *err = 0;

	LLVMMemoryBufferRef ll_f = 0;
	LLVMModuleRef m = 0;

	LLVMCreateMemoryBufferWithContentsOfFile(filename, &ll_f, &err);

	if (err != NULL) { 
		prt(err);
		return NULL;
	}
	
	LLVMParseIRInContext(LLVMGetGlobalContext(), ll_f, &m, &err);

	if (err != NULL) {
		prt(err);
	}

	return m;
}

void walkBasicblocks(LLVMValueRef function){

	//commonSubexpressions
	for (LLVMBasicBlockRef basicBlock = LLVMGetFirstBasicBlock(function); basicBlock; basicBlock = LLVMGetNextBasicBlock(basicBlock)) {
		walkBBInstructionsCSE(basicBlock);
	}

	//dead code
	for (LLVMBasicBlockRef basicBlock = LLVMGetFirstBasicBlock(function); basicBlock; basicBlock = LLVMGetNextBasicBlock(basicBlock)) {
		walkBBInstructionsDeadCode(basicBlock);
	}


	if(localOnly){
		constantFolding(function);
	}else{
		bool isChanged = true;

		while(isChanged){
			bool a = constantPropagation(function)
			bool b = constantFolding(function);
			isChanged = a | b;
		}
	}

	//commonSubexpressions
	for (LLVMBasicBlockRef basicBlock = LLVMGetFirstBasicBlock(function); basicBlock; basicBlock = LLVMGetNextBasicBlock(basicBlock)) {
		walkBBInstructionsCSE(basicBlock);
	}

	//dead code
	for (LLVMBasicBlockRef basicBlock = LLVMGetFirstBasicBlock(function); basicBlock; basicBlock = LLVMGetNextBasicBlock(basicBlock)) {
		walkBBInstructionsDeadCode(basicBlock);
	}

}

void walkFunctions(LLVMModuleRef module){
	for (LLVMValueRef function =  LLVMGetFirstFunction(module); 
			function; 
			function = LLVMGetNextFunction(function)) {

		const char* funcName = LLVMGetValueName(function);	

		printf("Function Name: %s\n", funcName);

		walkBasicblocks(function);
 	}
}

void walkGlobalValues(LLVMModuleRef module){
	for (LLVMValueRef gVal =  LLVMGetFirstGlobal(module);
                        gVal;
                        gVal = LLVMGetNextGlobal(gVal)) {

                const char* gName = LLVMGetValueName(gVal);
                printf("Global variable name: %s\n", gName);
        }
}

int main(int argc, char** argv)
{
	LLVMModuleRef m;

	if (argc == 2){
		m = createLLVMModel(argv[1]);
	}
	else if (argc == 3 && strcmp(argv[2], "--local") == 0){
		localOnly = true;
		m = createLLVMModel(argv[1]);
	}
	else{
		m = NULL;
		return 1;
	}

	if (m != NULL){
		//LLVMDumpModule(m);
		walkGlobalValues(m);
		walkFunctions(m);
		LLVMPrintModuleToFile (m, "test_new.ll", NULL);
	}
	else {
	    fprintf(stderr, "m is NULL\n");
	}
	
	return 0;
}


/*
void walkBBInstructions(LLVMBasicBlockRef bb){
	for (LLVMValueRef instruction = LLVMGetFirstInstruction(bb); instruction;
  				instruction = LLVMGetNextInstruction(instruction)) {
	
		// LLVMGetInstructionOpcode gives you LLVMOpcode that is a enum		
		LLVMOpcode op = LLVMGetInstructionOpcode(instruction);
    
		if (LLVMIsABranchInst(instruction)){
				printf("Branch inst: ");
				fflush(stdout); // Why do we need this?
				LLVMDumpValue(instruction);
				printf("\n Number of operands %d\n", LLVMGetNumOperands(instruction));
				/*
				if (LLVMIsConditional(instruction)){
					LLVMValueRef b1 = LLVMGetOperand(instruction, 1); 
					LLVMValueRef b2 = LLVMGetOperand(instruction, 2);
				
					printf("\n");
					printf("First target of a conditional branch instruction \n");
					LLVMDumpValue(b1);
					printf("Second target of a condistional branch instruction \n");
					LLVMDumpValue(b2);
					printf("\n");
				} 
			}

			// Construct Gen Set
			if ( op == LLVMStore ){
				LLVMValueRef destination = LLVMGetOperand(instruction, 1);
				for (LLVMValueRef currI : genSets[bb]){
					LLVMValueRef currDestination = LLVMGetOperand(currI, 1);
					if (destination == currDestination){
						genSets[bb].erase(currI);
					}
					genSets[bb].insert(instruction);
					break; 
				}
			}
	
			// Construct Kill Set
			if ( op == LLVMStore ) {
				LLVMValueRef destination = LLVMGetOperand(instruction, 1);
				for ( LLVMValueRef currI : totalStoreSet){
					LLVMValueRef currDestination = LLVMGetOperand(currI, 1);
					if (currDestination == destination && currI != instruction && !killSets[bb].contains(currI)){
						killSets[bb].insert(currI);
					}
				}
			}
	
	
			
			
			if (op == LLVMAdd) {
				printf("Found add instruction\n");
				LLVMDumpValue(instruction);		
				printf("\n");
	
				/*
				//Checking if one of the operands in a constant
				if (LLVMIsConstant(LLVMGetOperand(instruction, 0)) ||  
						LLVMIsConstant(LLVMGetOperand(instruction, 1))) {
				// Walking over all uses of an instruction
					LLVMUseRef y = LLVMGetFirstUse(instruction);
					if (y == NULL) printf("No uses\n");
					else printf("\n Exploring users of add with constant operand:\n");
					for (LLVMUseRef u = LLVMGetFirstUse(instruction);
						u;
						u = LLVMGetNextUse(u)){
						LLVMValueRef x = LLVMGetUser(u);
						LLVMDumpValue(x);
						printf("\n");
	
					}
				}
			}
	 }
	}*/