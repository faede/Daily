#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
//#include <vector>
#include "llvm/Analysis/LoopInfo.h"

using namespace llvm;


//#undef LLVM_ENABLE_ABI_BREAKING_CHECKS 
namespace{
	struct FuncBlockCount : public FunctionPass{
		static char ID;
		FuncBlockCount() : FunctionPass(ID){}
		
		// count blocks 
		void countBlocksInLoop(Loop * L, unsigned nest){
			unsigned num_Blocks = 0;
			Loop::block_iterator bb;
			for(bb = L->block_begin(); bb != L->block_end(); ++bb)
				num_Blocks++; 
			errs() << "Loop level " << nest << " has " << num_Blocks << " blocks\n";
			std::vector<Loop *> subLoops = L->getSubLoops();
			Loop::iterator j, f;
			for(j = subLoops.begin(), f = subLoops.end(); j != f; ++j)
				countBlocksInLoop(*j, nest + 1);
		}

		// rewrite function
		virtual void getAnalysisUsage(AnalysisUsage &AU) const {
            AU.setPreservesCFG();
            AU.addRequired<LoopInfoWrapperPass>();
        }
		// every function
		virtual bool runOnFunction(Function & F) {
			LoopInfo  *LI = &getAnalysis<LoopInfoWrapperPass>().getLoopInfo();
			errs() << "Functinon " << F.getName() + "\n";
			for(Loop * L :  *LI){
				countBlocksInLoop(L, 0);
			}
			return false;
		}
	};
};
char FuncBlockCount::ID = 0;
static RegisterPass<FuncBlockCount> X("funcblockcount", "Function Block Count", false, false);
