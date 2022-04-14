

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



### second

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





### new pass manager

https://llvm.org/docs/WritingAnLLVMPass.html#introduction-what-is-a-pass

