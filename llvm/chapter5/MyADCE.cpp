//===- DCE.cpp - Code to perform dead code elimination --------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file implements the Aggressive Dead Code Elimination pass.  This pass
// optimistically assumes that all instructions are dead until proven otherwise,
// allowing it to eliminate dead computations that other DCE passes do not
// catch, particularly involving loop computations.
//
//===----------------------------------------------------------------------===//

#include "llvm/InitializePasses.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/IR/Function.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/ADT/SmallPtrSet.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/InstIterator.h"


using namespace llvm;

#define DEBUG_TYPE "myadce"



namespace {
struct MyADCELegacyPass : public FunctionPass {
  static char ID; // Pass identification, replacement for typeid
  MyADCELegacyPass() : FunctionPass(ID) {
    initializeMyADCELegacyPassPass(*PassRegistry::getPassRegistry());
  }

  bool runOnFunction(Function &F) override;

  void getAnalysisUsage(AnalysisUsage &AU) const override {
    AU.setPreservesCFG();
  }
};
} // namespace

char MyADCELegacyPass::ID = 0;
INITIALIZE_PASS(MyADCELegacyPass, DEBUG_TYPE, 
        "My Aggressive Dead Code Elimination", 
        false,
        false)

bool MyADCELegacyPass::runOnFunction(Function &F) {
  if (skipFunction(F))
    return false;

  SmallPtrSet<Instruction *, 32> Alive;
  SmallVector<Instruction *, 128> Worklist;

  // Collect the set of "root" instructions that are known live.
  for (Instruction &I : instructions(F)) {
    if (I.isDebugOrPseudoInst() || !I.isSafeToRemove()) {
      Alive.insert(&I);
      Worklist.push_back(&I);
    }
  }

  // Propagate liveness backwards to operands.
  while (!Worklist.empty()) {
    Instruction *Curr = Worklist.pop_back_val();
    for (Use &OI : Curr->operands()) {
      if (Instruction *Inst = dyn_cast<Instruction>(OI))
        if (Alive.insert(Inst).second)
          Worklist.push_back(Inst);
    }
  }

  // The inverse of the live set is the dead set.  These are those instructions
  // which have no side effects and do not influence the control flow or return
  // value of the function, and may therefore be deleted safely.
  // NOTE: We reuse the Worklist vector here for memory efficiency.
  for (Instruction &I : instructions(F)) {
    if (!Alive.count(&I)) {
      Worklist.push_back(&I);
      I.dropAllReferences();
    }
  }

  for (Instruction *&I : Worklist) {
    I->eraseFromParent();
  }

  return !Worklist.empty();
}


FunctionPass *llvm::createMyADCELegacyPass() {
    return new MyADCELegacyPass();
}