//===----- VarValueDependencySlicer.cpp-Removing code dependant on value of variable -----===//
//
//              SimpLL - Program simplifier for analysis of semantic difference              //
//
// This file is published under Apache 2.0 license. See LICENSE for details.
// Author:
//===-------------------------------------------------------------------------------------===//
///
/// \file
/// This file contains the implementation of the VarValueDependencySlicer pass.
/// The pass slice the program to a value of a global variable.
///
//===-------------------------------------------------------------------------------------===//

#include <utility>
#include <Config.h>
#include <Utils.h>
#include "DebugInfo.h"
#include "VarValueDependencySlicer.h"
#include <llvm/IR/GlobalVariable.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Constant.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/IR/GlobalValue.h>
#include <llvm/IR/InstrTypes.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/IR/Constants.h>

using namespace llvm;

PreservedAnalyses VarValueDependencySlicer::run(Module &Mod,
                                           ModuleAnalysisManager &mam,
                                           GlobalVariable *Var,
                                           std::string VarValue) {
    Constant *initializer, *newConst;
    SmallVector<Instruction*,128> *listOfLoadInstructions = new SmallVector<Instruction*,128>();
    SmallVector<std::pair<Instruction*,int>,128> *listOfLoadUsersInstructions =
            new SmallVector<std::pair<Instruction*,int>,128>();

    if(Var->hasInitializer())
        initializer = Var->getInitializer();
    else 
        return PreservedAnalyses::none();

    if(VarValue != "default"){
        newConst = getConstantFromString(initializer, VarValue);

        if(newConst == NULL)
            return PreservedAnalyses::none();
    }
    else
        newConst = initializer;


    for(User *user: Var->users()){
        if(Instruction *instr = dyn_cast<Instruction>(user)) {
            if (LoadInst *loadInst = dyn_cast<LoadInst>(instr)) {
               listOfLoadInstructions->push_back(instr);

                for (User *instrUser: instr->users()) {
                    if (Instruction * instrOfGv = dyn_cast<Instruction>(instrUser)) {
                        int index = GetIndexOfGlobalVariableOperand(instrOfGv, instr);
                        listOfLoadUsersInstructions->push_back(std::make_pair(instrOfGv,index));
                   }
                }
            }
        }
    }

    while (!listOfLoadUsersInstructions->empty()) {
        std::pair<Instruction*,int> pair = listOfLoadUsersInstructions->pop_back_val();
        Instruction *instruction = pair.first;
        int index = pair.second;

        instruction->setOperand(index, newConst);
    }

    while (!listOfLoadInstructions->empty()) {
        Instruction *instruction = listOfLoadInstructions->pop_back_val();
        instruction->eraseFromParent();
    }

    return PreservedAnalyses::all();
}

Constant* VarValueDependencySlicer::getConstantFromString(Constant *initializer, std::string Value)
{
    if (const ConstantInt *CI = dyn_cast<ConstantInt>(initializer)) {
        uint64_t val;
        int valtmp;
        try{
            valtmp = std::stoi(Value);
        }
        catch(const std::invalid_argument &ia){
            exit(10);
        }
        val = valtmp;
        ConstantInt *CI2 = ConstantInt::get(CI->getType(),val,true);

        return dyn_cast<Constant>(CI2);
    }

    if (const ConstantFP *CFP = dyn_cast<ConstantFP>(initializer)) {
        double val;
        try{
            val = std::stod(Value);
        }
        catch(const std::invalid_argument &ia){
            exit(10);
        }
        Constant *CFP2 = ConstantFP::get(CFP->getType(),val);

        return CFP2;
    }
    exit(10);
}

int VarValueDependencySlicer::GetIndexOfGlobalVariableOperand(Instruction *instrParent,
                                                              Instruction *globalVariableInstr) {
    for(int i=0; i < instrParent->getNumOperands(); i++) {
        if(instrParent->getOperand(i) == globalVariableInstr)
            return i;
    }
}
