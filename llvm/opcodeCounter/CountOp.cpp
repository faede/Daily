#define DEBUG_TYPE "opcodeCounter"
#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include <map>
using namespace llvm;

namespace{
    struct CountOpcode : public FunctionPass{
        // save map
        std::map<std::string, int> opcodeCounter;
        static char ID;
        
        CountOpcode() : FunctionPass(ID){ }
        
        virtual bool runOnFunction(Function &F) {
            
            llvm::outs() << "FunctionName:" << F.getName() << "\n";
            for(Function::iterator bb = F.begin(), e = F.end(); bb != e; ++bb){
                // fix bug "redefine e"
                for(BasicBlock::iterator i = bb->begin(), block_e = bb->end(); i != block_e; ++i){
                    if(opcodeCounter.find(i->getOpcodeName()) == opcodeCounter.end()){
                        // not find
                        opcodeCounter[i->getOpcodeName()] = 1;
                    }else{
                        // exist
                        opcodeCounter[i->getOpcodeName()] += 1;
                    }
                }
            }
            
            
            for(auto &v : opcodeCounter){
                llvm::outs() << v.first << ": " << v.second << "\n";
            }
            llvm::outs() << "\n";
            opcodeCounter.clear();
            return false;
        }
    };
}

char CountOpcode::ID = 0;
static RegisterPass<CountOpcode> X("opcodeCounter", "Count number of opcode in a functions", false, false);