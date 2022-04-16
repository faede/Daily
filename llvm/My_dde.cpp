#include "llvm/Transforms/Scalar.h"
#include "llvm/ADT/DepthFirstIterator.h"
#include "llvm/ADT/SmallPtrSet.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/CFG.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/IntrinsicInst.h"
#include "llvm/Pass.h"

// add
#include "llvm/InitializePasses.h"
using namespace llvm;
namespace {
    struct MYADCE : public FunctionPass{
        static char ID;
        MYADCE() : FunctionPass(ID){
            initializeMYADCEPass(*PassRegistry::getPassRegistry());
        }

        bool runOnFunction(Function & F) override;

        void getAnalysisUsage(AnalysisUsage & AU) const override{
            AU.setPreservesCFG();
        }
    };
}

char MYADCE::ID = 0;
INITIALIZE_PASS(MYADCE, "myadce","My Aggressive Dead Code Elimination",
        false,
        false)

bool MYADCE::runOnFunction(Function& F){
	if(skipFunction(F)){
    //if(skipOptnoneFunction(F)){
        return false;
    }

    // SmallPtrSet - This class implements a set 
    // which is optimized for holding SmallSize or less elements.
    SmallPtrSet<Instruction *, 32> Alive;
    // This is a 'vector' (really, a variable-sized array), 
    // optimized for the case when the array is small.
    SmallVector<Instruction *, 32> Worklist;

    // collect inst
    for(Instruction & I : instructions(F)){
    	if(I.isTerminator()  || isa<DbgInfoIntrinsic>(I)
            || isa<LandingPadInst>(I) || I.mayHaveSideEffects()){
        //if(isa<TerminatorInst>(I) || isa<DbgInfoIntrinsic>(I)
        //    || isa<LandingPadInst>(I) || I.mayHaveSideEffects()){
            Alive.insert(&I);
            Worklist.push_back(&I);
        }
    }

    // down-ward liveness
    while(!Worklist.empty()){
    	Instruction * Curr = Worklist.pop_back_val();
    	for(Use & OI : Curr->operands()){
    		if(Instruction * Inst = dyn_cast<Instruction>(OI)){
    			if(Alive.insert(Inst).second){
    				Worklist.push_back(Inst);
    			}
    		}
    	}
    }


    // eliminate code
    for(Instruction & I : instructions(F)){
    	if(!Alive.count(&I)){
    		Worklist.push_back(&I);
    		I.dropAllReferences();
    	}
    }

    for(Instruction *& I : Worklist){
    	I->eraseFromParent();
    }

    return !Worklist.empty();
}

FunctionPass *llvm::createMYAggressiveDCEPass(){
	return new MYADCE();
}