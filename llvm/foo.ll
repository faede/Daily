; ModuleID = 'foo.c'
source_filename = "foo.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @foo(i32 noundef %n, i32 noundef %m) #0 {
entry:
  %n.addr = alloca i32, align 4
  %m.addr = alloca i32, align 4
  %sum = alloca i32, align 4
  %c0 = alloca i32, align 4
  %c1 = alloca i32, align 4
  store i32 %n, i32* %n.addr, align 4
  store i32 %m, i32* %m.addr, align 4
  store i32 0, i32* %sum, align 4
  %0 = load i32, i32* %n.addr, align 4
  store i32 %0, i32* %c0, align 4
  br label %for.cond

for.cond:                                         ; preds = %for.inc5, %entry
  %1 = load i32, i32* %c0, align 4
  %cmp = icmp sgt i32 %1, 0
  br i1 %cmp, label %for.body, label %for.end7

for.body:                                         ; preds = %for.cond
  %2 = load i32, i32* %m.addr, align 4
  store i32 %2, i32* %c1, align 4
  br label %for.cond1

for.cond1:                                        ; preds = %for.inc, %for.body
  %3 = load i32, i32* %c1, align 4
  %cmp2 = icmp sgt i32 %3, 0
  br i1 %cmp2, label %for.body3, label %for.end

for.body3:                                        ; preds = %for.cond1
  %4 = load i32, i32* %c0, align 4
  %5 = load i32, i32* %c1, align 4
  %cmp4 = icmp sgt i32 %4, %5
  %6 = zext i1 %cmp4 to i64
  %cond = select i1 %cmp4, i32 1, i32 0
  %7 = load i32, i32* %sum, align 4
  %add = add nsw i32 %7, %cond
  store i32 %add, i32* %sum, align 4
  br label %for.inc

for.inc:                                          ; preds = %for.body3
  %8 = load i32, i32* %c1, align 4
  %dec = add nsw i32 %8, -1
  store i32 %dec, i32* %c1, align 4
  br label %for.cond1, !llvm.loop !4

for.end:                                          ; preds = %for.cond1
  br label %for.inc5

for.inc5:                                         ; preds = %for.end
  %9 = load i32, i32* %c0, align 4
  %dec6 = add nsw i32 %9, -1
  store i32 %dec6, i32* %c0, align 4
  br label %for.cond, !llvm.loop !6

for.end7:                                         ; preds = %for.cond
  %10 = load i32, i32* %sum, align 4
  ret i32 %10
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
