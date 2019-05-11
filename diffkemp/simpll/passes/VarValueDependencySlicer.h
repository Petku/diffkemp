//===----- VarValueDependencySlicer.h - Removing code dependant on value of variable -----===//
//
//              SimpLL - Program simplifier for analysis of semantic difference              //
//
// This file is published under Apache 2.0 license. See LICENSE for details.
// Author:
//===-------------------------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the VarValueDependencySlicer pass.
/// The pass slice the program to a value of a global variable.
///
//===-------------------------------------------------------------------------------------===//

#ifndef PROJECT_VARVALUEDEPENDENCYSLICER_H
#define PROJECT_VARVALUEDEPENDENCYSLICER_H

#include <llvm/IR/PassManager.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/GlobalVariable.h>
#include <llvm/IR/Instructions.h>


using namespace llvm;


class VarValueDependencySlicer : public PassInfoMixin<VarValueDependencySlicer> {
  public:
    PreservedAnalyses run(Module &Mod, ModuleAnalysisManager &mam,
                          GlobalVariable *Var, std::string VarValue);

  private:
    Constant* getConstantFromString(Constant *initializer, std::string VarValue);
    int GetIndexOfGlobalVariableOperand(Instruction *instrParent, Instruction *globalVariableInstr);
};


#endif //PROJECT_VARVALUEDEPENDENCYSLICER_H
