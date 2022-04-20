

### test on llvm 15

### optmize

example.c

```cpp
int main(int argc, char ** argv){
	int i, j, k, t = 0;
	for(i = 0; i < 10; i++){
		for(j = 0; j < 10; j++){
			for(k = 0; k < 10; k++){
				t ++;
			}
		}
		for(j = 0; j < 10; j++){
			t++;
		}
	}
	for(i = 0; i < 20; i++){
		for(j = 0; j < 20; j++){
			t++;
		}
		for(j = 0 ;j < 20; j++){
			t++;
		}
	}
	return t;

}
```

ir:

```llvm
; ModuleID = 'example.c'
source_filename = "example.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main(i32 noundef %argc, i8** noundef %argv) #0 {
entry:
  %retval = alloca i32, align 4
  %argc.addr = alloca i32, align 4
  %argv.addr = alloca i8**, align 8
  %i = alloca i32, align 4
  %j = alloca i32, align 4
  %k = alloca i32, align 4
  %t = alloca i32, align 4
  store i32 0, i32* %retval, align 4
  store i32 %argc, i32* %argc.addr, align 4
  store i8** %argv, i8*** %argv.addr, align 8
  store i32 0, i32* %t, align 4
  store i32 0, i32* %i, align 4
  br label %for.cond

for.cond:                                         ; preds = %for.inc18, %entry
  %0 = load i32, i32* %i, align 4
  %cmp = icmp slt i32 %0, 10
  br i1 %cmp, label %for.body, label %for.end20

for.body:                                         ; preds = %for.cond
  store i32 0, i32* %j, align 4
  br label %for.cond1

for.cond1:                                        ; preds = %for.inc8, %for.body
  %1 = load i32, i32* %j, align 4
  %cmp2 = icmp slt i32 %1, 10
  br i1 %cmp2, label %for.body3, label %for.end10

for.body3:                                        ; preds = %for.cond1
  store i32 0, i32* %k, align 4
  br label %for.cond4

for.cond4:                                        ; preds = %for.inc, %for.body3
  %2 = load i32, i32* %k, align 4
  %cmp5 = icmp slt i32 %2, 10
  br i1 %cmp5, label %for.body6, label %for.end

for.body6:                                        ; preds = %for.cond4
  %3 = load i32, i32* %t, align 4
  %inc = add nsw i32 %3, 1
  store i32 %inc, i32* %t, align 4
  br label %for.inc

for.inc:                                          ; preds = %for.body6
  %4 = load i32, i32* %k, align 4
  %inc7 = add nsw i32 %4, 1
  store i32 %inc7, i32* %k, align 4
  br label %for.cond4, !llvm.loop !4

for.end:                                          ; preds = %for.cond4
  br label %for.inc8

for.inc8:                                         ; preds = %for.end
  %5 = load i32, i32* %j, align 4
  %inc9 = add nsw i32 %5, 1
  store i32 %inc9, i32* %j, align 4
  br label %for.cond1, !llvm.loop !6

for.end10:                                        ; preds = %for.cond1
  store i32 0, i32* %j, align 4
  br label %for.cond11

for.cond11:                                       ; preds = %for.inc15, %for.end10
  %6 = load i32, i32* %j, align 4
  %cmp12 = icmp slt i32 %6, 10
  br i1 %cmp12, label %for.body13, label %for.end17

for.body13:                                       ; preds = %for.cond11
  %7 = load i32, i32* %t, align 4
  %inc14 = add nsw i32 %7, 1
  store i32 %inc14, i32* %t, align 4
  br label %for.inc15

for.inc15:                                        ; preds = %for.body13
  %8 = load i32, i32* %j, align 4
  %inc16 = add nsw i32 %8, 1
  store i32 %inc16, i32* %j, align 4
  br label %for.cond11, !llvm.loop !7

for.end17:                                        ; preds = %for.cond11
  br label %for.inc18

for.inc18:                                        ; preds = %for.end17
  %9 = load i32, i32* %i, align 4
  %inc19 = add nsw i32 %9, 1
  store i32 %inc19, i32* %i, align 4
  br label %for.cond, !llvm.loop !8

for.end20:                                        ; preds = %for.cond
  store i32 0, i32* %i, align 4
  br label %for.cond21

for.cond21:                                       ; preds = %for.inc38, %for.end20
  %10 = load i32, i32* %i, align 4
  %cmp22 = icmp slt i32 %10, 20
  br i1 %cmp22, label %for.body23, label %for.end40

for.body23:                                       ; preds = %for.cond21
  store i32 0, i32* %j, align 4
  br label %for.cond24

for.cond24:                                       ; preds = %for.inc28, %for.body23
  %11 = load i32, i32* %j, align 4
  %cmp25 = icmp slt i32 %11, 20
  br i1 %cmp25, label %for.body26, label %for.end30

for.body26:                                       ; preds = %for.cond24
  %12 = load i32, i32* %t, align 4
  %inc27 = add nsw i32 %12, 1
  store i32 %inc27, i32* %t, align 4
  br label %for.inc28

for.inc28:                                        ; preds = %for.body26
  %13 = load i32, i32* %j, align 4
  %inc29 = add nsw i32 %13, 1
  store i32 %inc29, i32* %j, align 4
  br label %for.cond24, !llvm.loop !9

for.end30:                                        ; preds = %for.cond24
  store i32 0, i32* %j, align 4
  br label %for.cond31

for.cond31:                                       ; preds = %for.inc35, %for.end30
  %14 = load i32, i32* %j, align 4
  %cmp32 = icmp slt i32 %14, 20
  br i1 %cmp32, label %for.body33, label %for.end37

for.body33:                                       ; preds = %for.cond31
  %15 = load i32, i32* %t, align 4
  %inc34 = add nsw i32 %15, 1
  store i32 %inc34, i32* %t, align 4
  br label %for.inc35

for.inc35:                                        ; preds = %for.body33
  %16 = load i32, i32* %j, align 4
  %inc36 = add nsw i32 %16, 1
  store i32 %inc36, i32* %j, align 4
  br label %for.cond31, !llvm.loop !10

for.end37:                                        ; preds = %for.cond31
  br label %for.inc38

for.inc38:                                        ; preds = %for.end37
  %17 = load i32, i32* %i, align 4
  %inc39 = add nsw i32 %17, 1
  store i32 %inc39, i32* %i, align 4
  br label %for.cond21, !llvm.loop !11

for.end40:                                        ; preds = %for.cond21
  %18 = load i32, i32* %t, align 4
  ret i32 %18
}

attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

!llvm.module.flags = !{!0, !1, !2}
!llvm.ident = !{!3}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 7, !"uwtable", i32 1}
!2 = !{i32 7, !"frame-pointer", i32 2}
!3 = !{!"clang version 14.0.0 (https://github.com/llvm/llvm-project.git f750c3d95a0c8bf1d21380ae753fce12010a7561)"}
!4 = distinct !{!4, !5}
!5 = !{!"llvm.loop.mustprogress"}
!6 = distinct !{!6, !5}
!7 = distinct !{!7, !5}
!8 = distinct !{!8, !5}
!9 = distinct !{!9, !5}
!10 = distinct !{!10, !5}
!11 = distinct !{!11, !5}

```



(first install xdot)

```shell
opt -passes=view-cfg -S  example.ll # open a window show the cfg
opt -passes=dot-cfg -S  example.ll
llvm-as < example.ll | opt -passes=view-cfg
clang -S -emit-llvm example.c &  llvm-as < example.ll | opt -passes=view-cfg
```

clang -emit-llvm -S add.c -o add.ll

```shell
opt --help # list passes
```



**remove the "noundef"** in IR file

```
noundef
```

This attribute applies to parameters and return values. If the value representation contains any undefined or poison bits, the behavior is undefined. Note that this does not refer to padding introduced by the type’s storage representation



dag

test.ll

```llvm
define i32 @test(i32 %a, i32 %b, i32 %c) {
    %add = add nsw i32 %a, %b
    %div = sdiv i32 %add, %c
    ret i32 %div
}
```

shell:

```shell
~/files/llvm/bin/llc -view-legalize-dags   test.ll 
```

- `-view-dag-combine1-dags` displays the DAG after being built, before the first optimization pass.
- `-view-legalize-dags` displays the DAG before Legalization.
- `-view-dag-combine2-dags` displays the DAG before the second optimization pass.
- `-view-isel-dags` displays the DAG before the Select phase.
- `-view-sched-dags` displays the DAG before Scheduling.

### writing a pass

```c++
#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
using namespace llvm;

namespace{
	struct FuncBlockCount : public FunctionPass{
		static char ID;
		FuncBlockCount() : FunctionPass(ID){}
		bool runOnFunction(Function & F) override{
			errs() << "Functinon " << F.getName() << '\n';
			return false;
		}
	};
};
char FuncBlockCount::ID = 0;
static RegisterPass<FuncBlockCount> X("funcblockcount", "Function Block Count", false, false);
```

create a new direction **FuncBlockCount**

in `/home/zyy/files/llvm-project/llvm/lib/Transforms/FuncBlockCount`

CMakeList.txt:

new:

```cmake
add_llvm_library( LLVMFuncBlockCount MODULE
  FuncBlockCount.cpp

  PLUGIN_TOOL
  opt
  )

```

in `/home/zyy/files/llvm-project/llvm/lib/Transforms` 

CMakeList.txt

```cmake
# add
add_subdirectory(FuncBlockCount)
```

in `build` do:

```shell
cmake ../
make
```

generate  `LLVMFuncBlockCount.so` in /home/zyy/files/llvm-project/build/lib

sample.c

```c
int foo(int n, int m){
	int sum = 0;
	int c0 ;
	for(c0 = n; c0 > 0; c0--){
		int c1 = m;
		for(; c1 > 0; c1--){
			sum += c0 > c1 ? 1: 0;
		}
	}
	return sum;
}
```

shell:

```shell
/home/zyy/files/llvm-project/build/bin/clang -O0 -S -emit-llvm sample.c -o sample.ll # generate ir
/home/zyy/files/llvm-project/build/bin/opt -load /home/zyy/files/llvm-project/build/lib/LLVMFuncBlockCount.so -funcblockcount -enable-new-pm=0 sample.ll


```

error:

```shell
➜  llvm git:(master) ✗ opt -load /home/zyy/files/llvm-project/build/lib/LLVMFuncBlockCount.so -funcblockcount sample.ll 
Error opening '/home/zyy/files/llvm-project/build/lib/LLVMFuncBlockCount.so': /home/zyy/files/llvm-project/build/lib/LLVMFuncBlockCount.so: undefined symbol: _ZN4llvm23EnableABIBreakingChecksE
  -load request ignored.
opt: Unknown command line argument '-funcblockcount'.  Try: 'opt --help'
opt: Did you mean '--unroll-count'?
```

fix :

```shell
both opt and clang compiler from file
and use "full path" (or uninstall other)
```

error:

```shell
/home/zyy/files/llvm-project/build/bin/opt: unknown pass name 'hello'
```

fix:

```shell
# out of date, so we neew add :  -enable-new-pm=0
 -enable-new-pm=0
 eg:
 /home/zyy/files/llvm-project/build/bin/opt -load /home/zyy/files/llvm-project/build/lib/LLVMHello.so -hello sample.ll  -enable-new-pm=0
```



### second FuncBlockCount

```cpp
#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
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
			errs() << "Loop level " << nest << " has" << num_Blocks << " blocks\n";
			std::vector<Loop *> subLoops = L->getSubLoops();
			Loop::iterator j, f;
			for(j = subLoops.begin(); f = subLoops.end(); j != f)
				countBlocksInLoop(*j, nest + 1);
		}

		// every function
		virtual bool runOnFunction(Function & F) {
			LoopInfo * LI = &getAnalysis<LoopInfoWrapperPass>().getLoopInfo();
			errs() << "Functinon " << F.getName() << '\n';
			for(Loop * L : * LI){
				countBlocksInLoop(L, 0);
			}
			return false;
		}
	};
};
char FuncBlockCount::ID = 0;
static RegisterPass<FuncBlockCount> X("funcblockcount", "Function Block Count", false, false);

```

shell:

```shell
clang -O0 -S -emit-llvm sample.c -o sample.ll 

opt -load ~/files/llvm-project/build/lib/LLVMFuncBlockCount.so -funcblockcount sample.ll -enable-new-pm=0
```

error:

```shell
opt: /home/zyy/files/llvm-project/llvm/include/llvm/PassAnalysisSupport.h:243: AnalysisType& llvm::Pass::getAnalysisID(llvm::AnalysisID) const [with AnalysisType = llvm::LoopInfoWrapperPass; llvm::AnalysisID = const void*]: Assertion `ResultPass && "getAnalysis*() called on an analysis that was not " "'required' by pass!"' failed.
```

fix:

https://stackoverflow.com/questions/30351725/llvm-loopinfo-in-functionpass-doesnt-compile

actually: https://llvm.org/docs/WritingAnLLVMPass.html#the-getanalysis-and-getanalysisifavailable-methods

```
The Pass::getAnalysis<> method is automatically inherited by your class, providing you with access to the passes that you declared that you required with the getAnalysisUsage method. It takes a single template argument that specifies which pass class you want, and returns a reference to that pass. 
```

code:

```cpp
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
            // AU.setPreservesCFG();
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

```

output:

```shell
Functinon main
Loop level 0 has 11 blocks
Loop level 1 has 3 blocks
Loop level 1 has 3 blocks
Loop level 0 has 15 blocks
Loop level 1 has 7 blocks
Loop level 2 has 3 blocks
Loop level 1 has 3 blocks
```

### Opcode Analysis

```cpp
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
```

ans:

```shell
➜  llvm git:(master) ✗ opt -load ~/files/llvm-project/build/lib/LLVMCountopcodes.so -opcodeCounter testcode.bc -disable-output -enable-new-pm=0
FunctionName:func
add: 3
alloca: 5
br: 8
icmp: 3
load: 10
ret: 1
select: 1
store: 8
zext: 1
```

### AA

EverythingMustAlias.cpp

error :

```cpp
#include "llvm/Pass.h"
#include "llvm/Analysis/AliasAnalysis.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
using namespace llvm;

namespace {
    
    INITIALIZE_AG_PASS(EverythingMustAlias, AliasAnalysis, "must-aa", 
                "Everything Alias(always return 'must' alias)", 
                true, 
                true, 
                true);
    
    struct EverythingMustAlias : public ImmutablePass , public AliasAnalysis{
        static char ID;
        EverythingMustAlias() : ImmutablePass(ID) {}
        
        EverythingMustAliasPass() : FunctionPass(ID){
            initializeEverythingMustAliasPass(*PassRegistry::getPassRegistry());
        }


        void getAnalysisUsage(AnalysisUsage &AU) const {
            AU.setPreservesAll();
            // AliasAnalysis::getAnalysisUsage(AU);
            // declare your dependencies here.
        }   
        void *getAdjustedAnalysisPointer(const void* ID) override {
            if (ID == &AliasAnalysis::ID)
                return (AliasAnalysis*)this;
            return this;
        }   

        bool doInitialization(Module &M) override{
            const DataLayout * DL = &M.getDataLayout();
            return true;
        } 

        ImmutablePass * llvm::createEverythingMustAliasPass(){
            return new EverythingMustAlias();
        }

        bool run(Module &M) {
            //InitializeAliasAnalysis(this);
            doInitialization(M);
            // Perform analysis here...
            return false;
        }   
    };
}

char EverythingMustAlias::ID = 0;



```

testcode1.c

```c
void func(){
    int i;
    char C[2];
    char A[10];
    for(int i = 0; i != 10; i++){
        ((short *)C)[0] = A[i];
        C[1] = A[9-i];
    }
}
```

other aa:

```shell
➜  llvm git:(master) ✗ clang -c -emit-llvm testcode1.c -o testcode1.bc
➜  llvm git:(master) ✗ opt -aa-eval  -disable-output testcode1.bc  -enable-new-pm=0
===== Alias Analysis Evaluator Report =====
  10 Total Alias Queries Performed
  8 no alias responses (80.0%)
  1 may alias responses (10.0%)
  1 partial alias responses (10.0%)
  0 must alias responses (0.0%)
  Alias Analysis Evaluator Pointer Alias Summary: 80%/10%/10%/0%
  Alias Analysis Mod/Ref Evaluator Summary: no mod/ref!
➜  llvm git:(master) ✗ opt -print-dom-info  -disable-output testcode1.bc  -enable-new-pm=0
=============================--------------------------------
Inorder Dominator Tree: DFSNumbers invalid: 0 slow queries.
  [1] %entry {4294967295,4294967295} [0]
    [2] %for.cond {4294967295,4294967295} [1]
      [3] %for.body {4294967295,4294967295} [2]
        [4] %for.inc {4294967295,4294967295} [3]
      [3] %for.end {4294967295,4294967295} [2]
Roots: %entry
```

### test on llvm 12

### optimize pass MyADCELegacyPass

ref: **"llvm cookbook"**

https://csstormq.github.io/blog/LLVM%20%E4%B9%8B%20IR%20%E7%AF%87%EF%BC%884%EF%BC%89%EF%BC%9A%E5%A6%82%E4%BD%95%E5%9F%BA%E4%BA%8E%E4%BC%A0%E7%BB%9F%20Pass%20%E6%A1%86%E6%9E%B6%E6%89%A9%E5%B1%95%20LLVM%20IR%20%E4%BC%98%E5%8C%96%E5%99%A8

```
we need rename function by adding 'Legacy' keyword, or will terminal with error
```



```
-S                    - Write output as LLVM assembly
```

testcode.ll

```llvm
declare i32 @strlen(i8*) readonly nounwind
define void @test(){
    call i32 @strlen (i8* null)
    ret void
}
```

MyADCE.cpp in `llvm/lib/Transforms/Scalar`

```cpp
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
```

replace old code: **lib/IR/Instruction.cpp ** `isa`

```c++
bool Instruction::isDebugOrPseudoInst() const {
   return isa<DbgInfoIntrinsic>(this) || isa<PseudoProbeInst>(this);
 }

 bool Instruction::isSafeToRemove() const {
   return (!isa<CallInst>(this) || !this->mayHaveSideEffects()) &&
          !this->isTerminator() && !this->isEHPad();
 }

```

**lib/IR/Pass.cpp**  `inst_range`

```c++
 bool FunctionPass::skipFunction(const Function &F) const {
   OptPassGate &Gate = F.getContext().getOptPassGate();
   if (Gate.isEnabled() && !Gate.shouldRunPass(this, getDescription(F)))
     return true;
  
   if (F.hasOptNone()) {
     LLVM_DEBUG(dbgs() << "Skipping pass '" << getPassName() << "' on function "
                       << F.getName() << "\n");
     return true;
   }
   return false;
 }
```

and **include/llvm/IR/InstIterator.h**

```c++
inst_range 	llvm::instructions (Function *F)
```



in `llvm/include/llvm/InitializePasses.h`

```c++
void initializeMyADCELegacyPassPass(PassRegistry&);
```

in `llvm/include/llvm/LinkAllPasses.h` (optional)

```c++
(void) llvm::createMyADCELegacyPass();
```

```c++
// LinkAllPasses.h
namespace {
  struct ForcePassLinking {
    ForcePassLinking() {
      // We must reference the passes in such a way that compilers will not
      // delete it all as dead code, even with whole program optimization,
      // yet is effectively a NO-OP. As the compiler isn't smart enough
      // to know that getenv() never returns -1, this will do the job.
```

in `llvm/include/llvm/Transforms/Scalar.h`

```c++
FunctionPass *createMyADCELegacyPass();
```

in `llvm/include/llvm-c/Transforms/Scalar.h`

```c++
void LLVMAddMYAggressiveDCELegacyPass(LLVMPassManagerRef PM);
```

in `llvm/lib/Transforms/Scalar/Scalar.cpp`

```c++
void llvm::initializeScalarOpts(PassRegistry &Registry) {
  ...
  initializeMyADCELegacyPassPass(Registry);
}
```

and

```c++
void LLVMAddMYAggressiveDCELegacyPass(LLVMPassManagerRef PM) {
  unwrap(PM)->add(createMyADCELegacyPass());
}
```

in `llvm/lib/Transforms/Scalar/CMakeLists.txt`

```cmake
MyADCE.cpp
```

res:

```shell
➜  llvm git:(master) ✗ opt -S -myadce testcode.ll
; ModuleID = 'testcode.ll'
source_filename = "testcode.ll"

; Function Attrs: nounwind readonly
declare i32 @strlen(i8*) #0

define void @test() {
  ret void
}

attributes #0 = { nounwind readonly }

```



### DEC.cpp llvm12 code reading

profile:

```
-dce: Dead Code Elimination
Dead code elimination is similar to dead instruction elimination, but it rechecks instructions that were used by removed instructions to see if they are newly dead.
-die: Dead Instruction Elimination
Dead instruction elimination performs a single pass over the function, removing instructions that are obviously dead.
```



```c++
//===- DCE.cpp - Code to perform dead code elimination --------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements dead inst elimination and dead code elimination.
//
// Dead Inst Elimination performs a single pass over the function removing
// instructions that are obviously dead.  Dead Code Elimination is similar, but
// it rechecks instructions that were used by removed instructions to see if
// they are newly dead.
//
//===----------------------------------------------------------------------===//

#include "llvm/Transforms/Scalar/DCE.h"
#include "llvm/ADT/SetVector.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/Analysis/TargetLibraryInfo.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/IR/Instruction.h"
#include "llvm/InitializePasses.h"
#include "llvm/Pass.h"
#include "llvm/Support/DebugCounter.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Transforms/Utils/AssumeBundleBuilder.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"
#include "llvm/Transforms/Utils/Local.h"
using namespace llvm;

#define DEBUG_TYPE "dce"

STATISTIC(DCEEliminated, "Number of insts removed");
DEBUG_COUNTER(DCECounter, "dce-transform",
              "Controls which instructions are eliminated");

//===--------------------------------------------------------------------===//
// RedundantDbgInstElimination pass implementation
//

namespace {
struct RedundantDbgInstElimination : public FunctionPass {
  static char ID; // Pass identification, replacement for typeid
  RedundantDbgInstElimination() : FunctionPass(ID) {
    initializeRedundantDbgInstEliminationPass(*PassRegistry::getPassRegistry());
  }
/*
 bool FunctionPass::skipFunction(const Function &F) const 
   // Extensions to this class implement mechanisms 
   // to disable passes and individual optimizations at compile time.
   OptPassGate &Gate = F.getContext().getOptPassGate();
   if (Gate.isEnabled() && !Gate.shouldRunPass(this, getDescription(F)))
     return true;
   
   // Do not optimize this function (-O0).
   // bool hasOptNone() const { return hasFnAttribute(Attribute::OptimizeNone); }
   if (F.hasOptNone()) {
     LLVM_DEBUG(dbgs() << "Skipping pass '" << getPassName() << "' on function "
                       << F.getName() << "\n");
     return true;
   }
   return false;
 }
  
  
*/
  bool runOnFunction(Function &F) override {
    if (skipFunction(F))
      return false;
    bool Changed = false;
      
    /// Try to remove redundant dbg.value instructions from given basic block.
	/// Returns true if at least one instruction was removed. Remove redundant
	/// pseudo ops when RemovePseudoOp is true.
	// bool RemoveRedundantDbgInstrs(BasicBlock *BB, bool RemovePseudoOp = false);
    for (auto &BB : F)
      Changed |= RemoveRedundantDbgInstrs(&BB);
    return Changed;
  }

  void getAnalysisUsage(AnalysisUsage &AU) const override {
    // don't change the CFG
    AU.setPreservesCFG();
  }
};
}

char RedundantDbgInstElimination::ID = 0;
INITIALIZE_PASS(RedundantDbgInstElimination, "redundant-dbg-inst-elim",
                "Redundant Dbg Instruction Elimination", false, false)

Pass *llvm::createRedundantDbgInstEliminationPass() {
  return new RedundantDbgInstElimination();
}

PreservedAnalyses
RedundantDbgInstEliminationPass::run(Function &F, FunctionAnalysisManager &AM) {
  bool Changed = false;
  for (auto &BB : F)
    Changed |= RemoveRedundantDbgInstrs(&BB);
  if (!Changed)
    return PreservedAnalyses::all();
  PreservedAnalyses PA;
  PA.preserveSet<CFGAnalyses>();
  return PA;
}

//===--------------------------------------------------------------------===//
// DeadCodeElimination pass implementation
//

/*
 //===----------------------------------------------------------------------===//
 //  Local dead code elimination.
 //
  
 /// isInstructionTriviallyDead - Return true if the result produced by the
 /// instruction is not used, and the instruction has no side effects.
 ///
 bool llvm::isInstructionTriviallyDead(Instruction *I,
                                       const TargetLibraryInfo *TLI) {
   if (!I->use_empty())
     return false;
   return wouldInstructionBeTriviallyDead(I, TLI);
 }


bool llvm::wouldInstructionBeTriviallyDead(Instruction *I,
                                            const TargetLibraryInfo *TLI) {
   
   // static inline bool isTerminator(unsigned OpCode) {
   //   return OpCode >= TermOpsBegin && OpCode < TermOpsEnd;
   // }
   if (I->isTerminator())
     return false;
  
   // We don't want the landingpad-like instructions removed by anything this
   // general.
   if (I->isEHPad())
     return false;
  
   // We don't want debug info removed by anything this general, unless
   // debug info is empty.
   if (DbgDeclareInst *DDI = dyn_cast<DbgDeclareInst>(I)) {
     if (DDI->getAddress())
       return false;
     return true;
   }
   if (DbgValueInst *DVI = dyn_cast<DbgValueInst>(I)) {
     if (DVI->hasArgList() || DVI->getValue(0))
       return false;
     return true;
   }
   if (DbgLabelInst *DLI = dyn_cast<DbgLabelInst>(I)) {
     if (DLI->getLabel())
       return false;
     return true;
   }
  
   if (!I->willReturn())
     return false;
  
   if (!I->mayHaveSideEffects())
     return true;
  
   // Special case intrinsics that "may have side effects" but can be deleted
   // when dead.
   if (IntrinsicInst *II = dyn_cast<IntrinsicInst>(I)) {
     // Safe to delete llvm.stacksave and launder.invariant.group if dead.
     if (II->getIntrinsicID() == Intrinsic::stacksave ||
         II->getIntrinsicID() == Intrinsic::launder_invariant_group)
       return true;
  
     if (II->isLifetimeStartOrEnd()) {
       auto *Arg = II->getArgOperand(1);
       // Lifetime intrinsics are dead when their right-hand is undef.
       if (isa<UndefValue>(Arg))
         return true;
       // If the right-hand is an alloc, global, or argument and the only uses
       // are lifetime intrinsics then the intrinsics are dead.
       if (isa<AllocaInst>(Arg) || isa<GlobalValue>(Arg) || isa<Argument>(Arg))
         return llvm::all_of(Arg->uses(), [](Use &Use) {
           if (IntrinsicInst *IntrinsicUse =
                   dyn_cast<IntrinsicInst>(Use.getUser()))
             return IntrinsicUse->isLifetimeStartOrEnd();
           return false;
         });
       return false;
     }
  
     // Assumptions are dead if their condition is trivially true.  Guards on
     // true are operationally no-ops.  In the future we can consider more
     // sophisticated tradeoffs for guards considering potential for check
     // widening, but for now we keep things simple.
     if ((II->getIntrinsicID() == Intrinsic::assume &&
          isAssumeWithEmptyBundle(cast<AssumeInst>(*II))) ||
         II->getIntrinsicID() == Intrinsic::experimental_guard) {
       if (ConstantInt *Cond = dyn_cast<ConstantInt>(II->getArgOperand(0)))
         return !Cond->isZero();
  
       return false;
     }
  
     if (auto *FPI = dyn_cast<ConstrainedFPIntrinsic>(I)) {
       Optional<fp::ExceptionBehavior> ExBehavior = FPI->getExceptionBehavior();
       return ExBehavior.getValue() != fp::ebStrict;
     }
   }
  
   if (isAllocationFn(I, TLI) && isAllocRemovable(cast<CallBase>(I), TLI))
     return true;
  
   if (CallInst *CI = isFreeCall(I, TLI))
     if (Constant *C = dyn_cast<Constant>(CI->getArgOperand(0)))
       return C->isNullValue() || isa<UndefValue>(C);
  
   if (auto *Call = dyn_cast<CallBase>(I))
     if (isMathLibCallNoop(Call, TLI))
       return true;
  
   return false;
 }
*/

// DCELegacyPass::runOnFunction() -> eliminateDeadCode() -> DCEInstruction()
// -> isInstructionTriviallyDead()
static bool DCEInstruction(Instruction *I,
                           SmallSetVector<Instruction *, 16> &WorkList,
                           const TargetLibraryInfo *TLI) {
  if (isInstructionTriviallyDead(I, TLI)) {
    if (!DebugCounter::shouldExecute(DCECounter))
      return false;

    salvageDebugInfo(*I);
    salvageKnowledge(I);

    // Null out all of the instruction's operands to see if any operand becomes
    // dead as we go.
    for (unsigned i = 0, e = I->getNumOperands(); i != e; ++i) {
      Value *OpV = I->getOperand(i);
      I->setOperand(i, nullptr);

      if (!OpV->use_empty() || I == OpV)
        continue;

      // If the operand is an instruction that became dead as we nulled out the
      // operand, and if it is 'trivially' dead, delete it in a future loop
      // iteration.
      if (Instruction *OpI = dyn_cast<Instruction>(OpV))
        if (isInstructionTriviallyDead(OpI, TLI))
          WorkList.insert(OpI);
    }

    I->eraseFromParent();
    ++DCEEliminated;
    return true;
  }
  return false;
}

// DCELegacyPass::runOnFunction() -> eliminateDeadCode() -> DCEInstruction()
static bool eliminateDeadCode(Function &F, TargetLibraryInfo *TLI) {
  bool MadeChange = false;
  SmallSetVector<Instruction *, 16> WorkList;
  // Iterate over the original function, only adding insts to the worklist
  // if they actually need to be revisited. This avoids having to pre-init
  // the worklist with the entire function's worth of instructions.
  for (inst_iterator FI = inst_begin(F), FE = inst_end(F); FI != FE;) {
    Instruction *I = &*FI;
    ++FI;

    // We're visiting this instruction now, so make sure it's not in the
    // worklist from an earlier visit.
    if (!WorkList.count(I))
      MadeChange |= DCEInstruction(I, WorkList, TLI);
  }

  while (!WorkList.empty()) {
    Instruction *I = WorkList.pop_back_val();
    MadeChange |= DCEInstruction(I, WorkList, TLI);
  }
  return MadeChange;
}

PreservedAnalyses DCEPass::run(Function &F, FunctionAnalysisManager &AM) {
  if (!eliminateDeadCode(F, &AM.getResult<TargetLibraryAnalysis>(F)))
    return PreservedAnalyses::all();

  PreservedAnalyses PA;
  PA.preserveSet<CFGAnalyses>();
  return PA;
}

namespace {
struct DCELegacyPass : public FunctionPass {
  static char ID; // Pass identification, replacement for typeid
  DCELegacyPass() : FunctionPass(ID) {
    initializeDCELegacyPassPass(*PassRegistry::getPassRegistry());
  }

  bool runOnFunction(Function &F) override {
    if (skipFunction(F))
      return false;

    TargetLibraryInfo *TLI =
        &getAnalysis<TargetLibraryInfoWrapperPass>().getTLI(F);

    return eliminateDeadCode(F, TLI);
  }

  void getAnalysisUsage(AnalysisUsage &AU) const override {
    AU.addRequired<TargetLibraryInfoWrapperPass>();
    AU.setPreservesCFG();
  }
};
}

char DCELegacyPass::ID = 0;
INITIALIZE_PASS(DCELegacyPass, "dce", "Dead Code Elimination", false, false)

FunctionPass *llvm::createDeadCodeEliminationPass() {
  return new DCELegacyPass();
}

```

`llvm/include/llvm/Transforms/Utils/BasicBlockUtils.h`

```c++
bool llvm::RemoveRedundantDbgInstrs(BasicBlock *BB) {
  bool MadeChanges = false;
  // By using the "backward scan" strategy before the "forward scan" strategy we
  // can remove both dbg.value (2) and (3) in a situation like this:
  //
  //   (1) dbg.value V1, "x", DIExpression()
  //       ...
  //   (2) dbg.value V2, "x", DIExpression()
  //   (3) dbg.value V1, "x", DIExpression()
  //
  // The backward scan will remove (2), it is made obsolete by (3). After
  // getting (2) out of the way, the foward scan will remove (3) since "x"
  // already is described as having the value V1 at (1).
  MadeChanges |= removeRedundantDbgInstrsUsingBackwardScan(BB);
  MadeChanges |= removeRedundantDbgInstrsUsingForwardScan(BB);

  if (MadeChanges)
    LLVM_DEBUG(dbgs() << "Removed redundant dbg instrs from: "
                      << BB->getName() << "\n");
  return MadeChanges;
}

/// Remove redundant instructions within sequences of consecutive dbg.value
/// instructions. This is done using a backward scan to keep the last dbg.value
/// describing a specific variable/fragment.
///
/// BackwardScan strategy:
/// ----------------------
/// Given a sequence of consecutive DbgValueInst like this
///
///   dbg.value ..., "x", FragmentX1  (*)
///   dbg.value ..., "y", FragmentY1
///   dbg.value ..., "x", FragmentX2
///   dbg.value ..., "x", FragmentX1  (**)
///
/// then the instruction marked with (*) can be removed (it is guaranteed to be
/// obsoleted by the instruction marked with (**) as the latter instruction is
/// describing the same variable using the same fragment info).
///
/// Possible improvements:
/// - Check fully overlapping fragments and not only identical fragments.
/// - Support dbg.addr, dbg.declare. dbg.label, and possibly other meta
///   instructions being part of the sequence of consecutive instructions.
static bool removeRedundantDbgInstrsUsingBackwardScan(BasicBlock *BB) {
  SmallVector<DbgValueInst *, 8> ToBeRemoved;
  SmallDenseSet<DebugVariable> VariableSet;
  for (auto &I : reverse(*BB)) {
    if (DbgValueInst *DVI = dyn_cast<DbgValueInst>(&I)) {
      DebugVariable Key(DVI->getVariable(),
                        DVI->getExpression(),
                        DVI->getDebugLoc()->getInlinedAt());
      auto R = VariableSet.insert(Key);
      // If the same variable fragment is described more than once it is enough
      // to keep the last one (i.e. the first found since we for reverse
      // iteration).
      if (!R.second)
        ToBeRemoved.push_back(DVI);
      continue;
    }
    // Sequence with consecutive dbg.value instrs ended. Clear the map to
    // restart identifying redundant instructions if case we find another
    // dbg.value sequence.
    VariableSet.clear();
  }

  for (auto &Instr : ToBeRemoved)
    Instr->eraseFromParent();

  return !ToBeRemoved.empty();
}
```

### BDCE.cpp

```c++
/// If an instruction is trivialized (dead), then the chain of users of that
/// instruction may need to be cleared of assumptions that can no longer be
/// guaranteed correct.
static void clearAssumptionsOfUsers(Instruction *I, DemandedBits &DB) {
  assert(I->getType()->isIntOrIntVectorTy() &&
         "Trivializing a non-integer value?");

  // Initialize the worklist with eligible direct users.
  SmallPtrSet<Instruction *, 16> Visited;
  SmallVector<Instruction *, 16> WorkList;
  for (User *JU : I->users()) {
    // If all bits of a user are demanded, then we know that nothing below that
    // in the def-use chain needs to be changed.
    auto *J = dyn_cast<Instruction>(JU);
    if (J && J->getType()->isIntOrIntVectorTy() &&
        !DB.getDemandedBits(J).isAllOnesValue()) {
      Visited.insert(J);
      WorkList.push_back(J);
    }

    // Note that we need to check for non-int types above before asking for
    // demanded bits. Normally, the only way to reach an instruction with an
    // non-int type is via an instruction that has side effects (or otherwise
    // will demand its input bits). However, if we have a readnone function
    // that returns an unsized type (e.g., void), we must avoid asking for the
    // demanded bits of the function call's return value. A void-returning
    // readnone function is always dead (and so we can stop walking the use/def
    // chain here), but the check is necessary to avoid asserting.
  }

  // DFS through subsequent users while tracking visits to avoid cycles.
  while (!WorkList.empty()) {
    Instruction *J = WorkList.pop_back_val();

    // NSW, NUW, and exact are based on operands that might have changed.
    J->dropPoisonGeneratingFlags();

    // We do not have to worry about llvm.assume or range metadata:
    // 1. llvm.assume demands its operand, so trivializing can't change it.
    // 2. range metadata only applies to memory accesses which demand all bits.

    for (User *KU : J->users()) {
      // If all bits of a user are demanded, then we know that nothing below
      // that in the def-use chain needs to be changed.
      auto *K = dyn_cast<Instruction>(KU);
      if (K && Visited.insert(K).second && K->getType()->isIntOrIntVectorTy() &&
          !DB.getDemandedBits(K).isAllOnesValue())
        WorkList.push_back(K);
    }
  }
}

```

bitTrackingDCE() -> clearAssumptionsOfUsers()

```c++
static bool bitTrackingDCE(Function &F, DemandedBits &DB) {
  SmallVector<Instruction*, 128> Worklist;
  bool Changed = false;
  
  /*           first                      */
  for (Instruction &I : instructions(F)) {
    // If the instruction has side effects and no non-dbg uses,
    // skip it. This way we avoid computing known bits on an instruction
    // that will not help us.
    if (I.mayHaveSideEffects() && I.use_empty())
      continue;
 
      
 /*
  bool DemandedBits::isUseDead(Use *U) {
   // We only track integer uses, everything else is assumed live.
   if (!(*U)->getType()->isIntOrIntVectorTy())
     return false;
  
   // Uses by always-live instructions are never dead.
   Instruction *UserI = cast<Instruction>(U->getUser());
   if (isAlwaysLive(UserI))
     return false;
  
   performAnalysis();
   if (DeadUses.count(U))
     return true;
  
   // If no output bits are demanded, no input bits are demanded and the use
   // is dead. These uses might not be explicitly present in the DeadUses map.
   if (UserI->getType()->isIntOrIntVectorTy()) {
     auto Found = AliveBits.find(UserI);
     if (Found != AliveBits.end() && Found->second.isZero())
       return true;
   }
  
   return false;
 }
 
 static bool isAlwaysLive(Instruction *I) {
   return I->isTerminator() || isa<DbgInfoIntrinsic>(I) || I->isEHPad() ||
          I->mayHaveSideEffects();
 }
 
 */     
      
    // Remove instructions that are dead, either because they were not reached
    // during analysis or have no demanded bits.
    if (DB.isInstructionDead(&I) ||
        (I.getType()->isIntOrIntVectorTy() &&
         DB.getDemandedBits(&I).isNullValue() &&
         wouldInstructionBeTriviallyDead(&I))) {
      salvageDebugInfo(I);
      Worklist.push_back(&I);
      I.dropAllReferences();
      Changed = true;
      continue;
    }

    // Convert SExt into ZExt if none of the extension bits is required
    if (SExtInst *SE = dyn_cast<SExtInst>(&I)) {
      APInt Demanded = DB.getDemandedBits(SE);
      const uint32_t SrcBitSize = SE->getSrcTy()->getScalarSizeInBits();
      auto *const DstTy = SE->getDestTy();
      const uint32_t DestBitSize = DstTy->getScalarSizeInBits();
      if (Demanded.countLeadingZeros() >= (DestBitSize - SrcBitSize)) {
        clearAssumptionsOfUsers(SE, DB);
        IRBuilder<> Builder(SE);
        I.replaceAllUsesWith(
            Builder.CreateZExt(SE->getOperand(0), DstTy, SE->getName()));
        Worklist.push_back(SE);
        Changed = true;
        NumSExt2ZExt++;
        continue;
      }
    }

    for (Use &U : I.operands()) {
      // DemandedBits only detects dead integer uses.
      if (!U->getType()->isIntOrIntVectorTy())
        continue;

      if (!isa<Instruction>(U) && !isa<Argument>(U))
        continue;

      if (!DB.isUseDead(&U))
        continue;

      LLVM_DEBUG(dbgs() << "BDCE: Trivializing: " << U << " (all bits dead)\n");

      clearAssumptionsOfUsers(&I, DB);

      // FIXME: In theory we could substitute undef here instead of zero.
      // This should be reconsidered once we settle on the semantics of
      // undef, poison, etc.
      U.set(ConstantInt::get(U->getType(), 0));
      ++NumSimplified;
      Changed = true;
    }
  }
  
  /*              second                      */
  for (Instruction *&I : Worklist) {
    ++NumRemoved;
    I->eraseFromParent();
  }

  return Changed;
}

```





fullfile:

```c++
//===---- BDCE.cpp - Bit-tracking dead code elimination -------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements the Bit-Tracking Dead Code Elimination pass. Some
// instructions (shifts, some ands, ors, etc.) kill some of their input bits.
// We track these dead bits and remove instructions that compute only these
// dead bits. We also simplify sext that generates unused extension bits,
// converting it to a zext.
//
//===----------------------------------------------------------------------===//

#include "llvm/Transforms/Scalar/BDCE.h"
#include "llvm/ADT/SmallPtrSet.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/Analysis/DemandedBits.h"
#include "llvm/Analysis/GlobalsModRef.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/IR/Instructions.h"
#include "llvm/InitializePasses.h"
#include "llvm/Pass.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Transforms/Utils/Local.h"
using namespace llvm;

#define DEBUG_TYPE "bdce"

STATISTIC(NumRemoved, "Number of instructions removed (unused)");
STATISTIC(NumSimplified, "Number of instructions trivialized (dead bits)");
STATISTIC(NumSExt2ZExt,
          "Number of sign extension instructions converted to zero extension");

/// If an instruction is trivialized (dead), then the chain of users of that
/// instruction may need to be cleared of assumptions that can no longer be
/// guaranteed correct.
static void clearAssumptionsOfUsers(Instruction *I, DemandedBits &DB) {
  assert(I->getType()->isIntOrIntVectorTy() &&
         "Trivializing a non-integer value?");

  // Initialize the worklist with eligible direct users.
  SmallPtrSet<Instruction *, 16> Visited;
  SmallVector<Instruction *, 16> WorkList;
  for (User *JU : I->users()) {
    // If all bits of a user are demanded, then we know that nothing below that
    // in the def-use chain needs to be changed.
    auto *J = dyn_cast<Instruction>(JU);
    if (J && J->getType()->isIntOrIntVectorTy() &&
        !DB.getDemandedBits(J).isAllOnesValue()) {
      Visited.insert(J);
      WorkList.push_back(J);
    }

    // Note that we need to check for non-int types above before asking for
    // demanded bits. Normally, the only way to reach an instruction with an
    // non-int type is via an instruction that has side effects (or otherwise
    // will demand its input bits). However, if we have a readnone function
    // that returns an unsized type (e.g., void), we must avoid asking for the
    // demanded bits of the function call's return value. A void-returning
    // readnone function is always dead (and so we can stop walking the use/def
    // chain here), but the check is necessary to avoid asserting.
  }

  // DFS through subsequent users while tracking visits to avoid cycles.
  while (!WorkList.empty()) {
    Instruction *J = WorkList.pop_back_val();

    // NSW, NUW, and exact are based on operands that might have changed.
    J->dropPoisonGeneratingFlags();

    // We do not have to worry about llvm.assume or range metadata:
    // 1. llvm.assume demands its operand, so trivializing can't change it.
    // 2. range metadata only applies to memory accesses which demand all bits.

    for (User *KU : J->users()) {
      // If all bits of a user are demanded, then we know that nothing below
      // that in the def-use chain needs to be changed.
      auto *K = dyn_cast<Instruction>(KU);
      if (K && Visited.insert(K).second && K->getType()->isIntOrIntVectorTy() &&
          !DB.getDemandedBits(K).isAllOnesValue())
        WorkList.push_back(K);
    }
  }
}

static bool bitTrackingDCE(Function &F, DemandedBits &DB) {
  SmallVector<Instruction*, 128> Worklist;
  bool Changed = false;
  for (Instruction &I : instructions(F)) {
    // If the instruction has side effects and no non-dbg uses,
    // skip it. This way we avoid computing known bits on an instruction
    // that will not help us.
    if (I.mayHaveSideEffects() && I.use_empty())
      continue;

    // Remove instructions that are dead, either because they were not reached
    // during analysis or have no demanded bits.
    if (DB.isInstructionDead(&I) ||
        (I.getType()->isIntOrIntVectorTy() &&
         DB.getDemandedBits(&I).isNullValue() &&
         wouldInstructionBeTriviallyDead(&I))) {
      salvageDebugInfo(I);
      Worklist.push_back(&I);
      I.dropAllReferences();
      Changed = true;
      continue;
    }

    // Convert SExt into ZExt if none of the extension bits is required
    if (SExtInst *SE = dyn_cast<SExtInst>(&I)) {
      APInt Demanded = DB.getDemandedBits(SE);
      const uint32_t SrcBitSize = SE->getSrcTy()->getScalarSizeInBits();
      auto *const DstTy = SE->getDestTy();
      const uint32_t DestBitSize = DstTy->getScalarSizeInBits();
      if (Demanded.countLeadingZeros() >= (DestBitSize - SrcBitSize)) {
        clearAssumptionsOfUsers(SE, DB);
        IRBuilder<> Builder(SE);
        I.replaceAllUsesWith(
            Builder.CreateZExt(SE->getOperand(0), DstTy, SE->getName()));
        Worklist.push_back(SE);
        Changed = true;
        NumSExt2ZExt++;
        continue;
      }
    }

    for (Use &U : I.operands()) {
      // DemandedBits only detects dead integer uses.
      if (!U->getType()->isIntOrIntVectorTy())
        continue;

      if (!isa<Instruction>(U) && !isa<Argument>(U))
        continue;

      if (!DB.isUseDead(&U))
        continue;

      LLVM_DEBUG(dbgs() << "BDCE: Trivializing: " << U << " (all bits dead)\n");

      clearAssumptionsOfUsers(&I, DB);

      // FIXME: In theory we could substitute undef here instead of zero.
      // This should be reconsidered once we settle on the semantics of
      // undef, poison, etc.
      U.set(ConstantInt::get(U->getType(), 0));
      ++NumSimplified;
      Changed = true;
    }
  }

  for (Instruction *&I : Worklist) {
    ++NumRemoved;
    I->eraseFromParent();
  }

  return Changed;
}

PreservedAnalyses BDCEPass::run(Function &F, FunctionAnalysisManager &AM) {
  auto &DB = AM.getResult<DemandedBitsAnalysis>(F);
  if (!bitTrackingDCE(F, DB))
    return PreservedAnalyses::all();

  PreservedAnalyses PA;
  PA.preserveSet<CFGAnalyses>();
  PA.preserve<GlobalsAA>();
  return PA;
}

namespace {
struct BDCELegacyPass : public FunctionPass {
  static char ID; // Pass identification, replacement for typeid
  BDCELegacyPass() : FunctionPass(ID) {
    initializeBDCELegacyPassPass(*PassRegistry::getPassRegistry());
  }

  bool runOnFunction(Function &F) override {
    if (skipFunction(F))
      return false;
    auto &DB = getAnalysis<DemandedBitsWrapperPass>().getDemandedBits();
    return bitTrackingDCE(F, DB);
  }

  void getAnalysisUsage(AnalysisUsage &AU) const override {
    AU.setPreservesCFG();
    AU.addRequired<DemandedBitsWrapperPass>();
    AU.addPreserved<GlobalsAAWrapperPass>();
  }
};
}

char BDCELegacyPass::ID = 0;
INITIALIZE_PASS_BEGIN(BDCELegacyPass, "bdce",
                      "Bit-Tracking Dead Code Elimination", false, false)
INITIALIZE_PASS_DEPENDENCY(DemandedBitsWrapperPass)
INITIALIZE_PASS_END(BDCELegacyPass, "bdce",
                    "Bit-Tracking Dead Code Elimination", false, false)

FunctionPass *llvm::createBitTrackingDCEPass() { return new BDCELegacyPass(); }

```



### inline

```c++
 #include "llvm/InitializePasses.h"
 #include "llvm/Transforms/IPO.h"
 #include "llvm/Transforms/IPO/Inliner.h"
 #include "llvm/Analysis/InlineCost.h"
 
 using namespace llvm;
 
 #define DEBUG_TYPE "myinliner"
 
 namespace {
 
 class MyInlinerLegacyPass : public LegacyInlinerBase {
 public:
   static char ID;
 
   MyInlinerLegacyPass() : LegacyInlinerBase(ID) {
     initializeMyInlinerLegacyPassPass(*PassRegistry::getPassRegistry());
   }
 
   InlineCost getInlineCost(CallBase &CB) override;
 };
 
 } // anonymous namespace
 
 InlineCost MyInlinerLegacyPass::getInlineCost(CallBase &CB) {
   if (!CB.hasFnAttr(Attribute::AlwaysInline)) {
     return InlineCost::getNever("no alwaysinline attribute");
   }
 
   Function *Callee = CB.getCalledFunction();
 
   if (!Callee) {
     return InlineCost::getNever("indirect function invocation");
   }
 
   if (Callee->isDeclaration()) {
     return InlineCost::getNever("no function definition");
   }
 
   if (Callee->isPresplitCoroutine()) {
     return InlineCost::getNever("unsplited coroutine call");
   }
 
   auto IsVisble = isInlineViable(*Callee);
   if (!IsVisble.isSuccess()) {
     return InlineCost::getNever(IsVisble.getFailureReason());
   }
 
   return InlineCost::getAlways("always inliner");
 }
 
 char MyInlinerLegacyPass::ID = 0;
 
 INITIALIZE_PASS(MyInlinerLegacyPass, DEBUG_TYPE,
                 "Inliner for always_inline functions Legacy Pass", false, false)
 
 Pass *llvm::createMyInlinerLegacyPass() {
   return new MyInlinerLegacyPass();
 }
```



IPO/IPO.cpp

```c++
  initializeMyInlinerLegacyPassPass(Registry);
  
// my pass
void LLVMAddMyInlinerLegacyPass(LLVMPassManagerRef PM) {
  unwrap(PM)->add(createMyInlinerLegacyPass());
}
```

CMakeList.txt

```cmake
MyINLINE.cpp
```

llvm-project/llvm/include/llvm/InitializePass.h

```c++
void initializeMyInlinerLegacyPassPass(PassRegistry&);
```

llvm-project/llvm/include/llvm/Transforms/IPO.h

```c++
Pass *createMyInlinerLegacyPass();
```

llvm-project/llvm/include/llvm-c/Transforms/IPO.h

```c++
void LLVMAddMyInlinerLegacyPass(LLVMPassManagerRef PM);
```



inline.ll

```llvm'
define i32 @inner1() alwaysinline {
  ret i32 1
}
define i32 @outer1() {
  %r = call i32 @inner1()
  ret i32 %r
}
```

res:

```shell
➜  llvm git:(master) ✗ opt -inline-threshold=0 -myinliner -S inline.ll 
; ModuleID = 'inline.ll'
source_filename = "inline.ll"

; Function Attrs: alwaysinline
define i32 @inner1() #0 {
  ret i32 1
}

define i32 @outer1() {
  ret i32 1
}

attributes #0 = { alwaysinline }
```

