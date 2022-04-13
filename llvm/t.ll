; ModuleID = 't.c'
source_filename = "t.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 !dbg !8 {
entry:
  %retval = alloca i32, align 4
  %a = alloca i32, align 4
  %b = alloca i32, align 4
  %i = alloca i32, align 4
  %c = alloca i32, align 4
  %d = alloca i32, align 4
  store i32 0, i32* %retval, align 4
  call void @llvm.dbg.declare(metadata i32* %a, metadata !13, metadata !DIExpression()), !dbg !14
  store i32 2, i32* %a, align 4, !dbg !14
  call void @llvm.dbg.declare(metadata i32* %b, metadata !15, metadata !DIExpression()), !dbg !16
  store i32 1, i32* %b, align 4, !dbg !16
  %0 = load i32, i32* %a, align 4, !dbg !17
  %cmp = icmp slt i32 %0, 3, !dbg !19
  br i1 %cmp, label %if.then, label %if.else, !dbg !20

if.then:                                          ; preds = %entry
  store i32 3, i32* %b, align 4, !dbg !21
  br label %if.end, !dbg !23

if.else:                                          ; preds = %entry
  store i32 5, i32* %b, align 4, !dbg !24
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  call void @llvm.dbg.declare(metadata i32* %i, metadata !26, metadata !DIExpression()), !dbg !28
  store i32 0, i32* %i, align 4, !dbg !28
  br label %for.cond, !dbg !29

for.cond:                                         ; preds = %for.inc, %if.end
  %1 = load i32, i32* %i, align 4, !dbg !30
  %cmp1 = icmp slt i32 %1, 1000, !dbg !32
  br i1 %cmp1, label %for.body, label %for.end, !dbg !33

for.body:                                         ; preds = %for.cond
  %2 = load i32, i32* %b, align 4, !dbg !34
  %inc = add nsw i32 %2, 1, !dbg !34
  store i32 %inc, i32* %b, align 4, !dbg !34
  br label %for.inc, !dbg !36

for.inc:                                          ; preds = %for.body
  %3 = load i32, i32* %i, align 4, !dbg !37
  %inc2 = add nsw i32 %3, 1, !dbg !37
  store i32 %inc2, i32* %i, align 4, !dbg !37
  br label %for.cond, !dbg !38, !llvm.loop !39

for.end:                                          ; preds = %for.cond
  call void @llvm.dbg.declare(metadata i32* %c, metadata !42, metadata !DIExpression()), !dbg !43
  store i32 2, i32* %c, align 4, !dbg !43
  call void @llvm.dbg.declare(metadata i32* %d, metadata !44, metadata !DIExpression()), !dbg !45
  %4 = load i32, i32* %b, align 4, !dbg !46
  %5 = load i32, i32* %c, align 4, !dbg !47
  %add = add nsw i32 %4, %5, !dbg !48
  store i32 %add, i32* %d, align 4, !dbg !45
  %6 = load i32, i32* %d, align 4, !dbg !49
  ret i32 %6, !dbg !50
}

; Function Attrs: nofree nosync nounwind readnone speculatable willreturn
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { nofree nosync nounwind readnone speculatable willreturn }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!2, !3, !4, !5, !6}
!llvm.ident = !{!7}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 14.0.0 (https://github.com/llvm/llvm-project.git f750c3d95a0c8bf1d21380ae753fce12010a7561)", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, splitDebugInlining: false, nameTableKind: None)
!1 = !DIFile(filename: "t.c", directory: "/home/zyy/files/GitHub/Daily/llvm", checksumkind: CSK_MD5, checksum: "844af37c2deef2c1cc964a240c52196f")
!2 = !{i32 7, !"Dwarf Version", i32 5}
!3 = !{i32 2, !"Debug Info Version", i32 3}
!4 = !{i32 1, !"wchar_size", i32 4}
!5 = !{i32 7, !"uwtable", i32 1}
!6 = !{i32 7, !"frame-pointer", i32 2}
!7 = !{!"clang version 14.0.0 (https://github.com/llvm/llvm-project.git f750c3d95a0c8bf1d21380ae753fce12010a7561)"}
!8 = distinct !DISubprogram(name: "main", scope: !1, file: !1, line: 2, type: !9, scopeLine: 2, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !12)
!9 = !DISubroutineType(types: !10)
!10 = !{!11}
!11 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!12 = !{}
!13 = !DILocalVariable(name: "a", scope: !8, file: !1, line: 3, type: !11)
!14 = !DILocation(line: 3, column: 6, scope: !8)
!15 = !DILocalVariable(name: "b", scope: !8, file: !1, line: 4, type: !11)
!16 = !DILocation(line: 4, column: 6, scope: !8)
!17 = !DILocation(line: 5, column: 5, scope: !18)
!18 = distinct !DILexicalBlock(scope: !8, file: !1, line: 5, column: 5)
!19 = !DILocation(line: 5, column: 7, scope: !18)
!20 = !DILocation(line: 5, column: 5, scope: !8)
!21 = !DILocation(line: 6, column: 5, scope: !22)
!22 = distinct !DILexicalBlock(scope: !18, file: !1, line: 5, column: 11)
!23 = !DILocation(line: 7, column: 2, scope: !22)
!24 = !DILocation(line: 8, column: 5, scope: !25)
!25 = distinct !DILexicalBlock(scope: !18, file: !1, line: 7, column: 7)
!26 = !DILocalVariable(name: "i", scope: !27, file: !1, line: 10, type: !11)
!27 = distinct !DILexicalBlock(scope: !8, file: !1, line: 10, column: 2)
!28 = !DILocation(line: 10, column: 10, scope: !27)
!29 = !DILocation(line: 10, column: 6, scope: !27)
!30 = !DILocation(line: 10, column: 17, scope: !31)
!31 = distinct !DILexicalBlock(scope: !27, file: !1, line: 10, column: 2)
!32 = !DILocation(line: 10, column: 19, scope: !31)
!33 = !DILocation(line: 10, column: 2, scope: !27)
!34 = !DILocation(line: 11, column: 4, scope: !35)
!35 = distinct !DILexicalBlock(scope: !31, file: !1, line: 10, column: 31)
!36 = !DILocation(line: 12, column: 2, scope: !35)
!37 = !DILocation(line: 10, column: 28, scope: !31)
!38 = !DILocation(line: 10, column: 2, scope: !31)
!39 = distinct !{!39, !33, !40, !41}
!40 = !DILocation(line: 12, column: 2, scope: !27)
!41 = !{!"llvm.loop.mustprogress"}
!42 = !DILocalVariable(name: "c", scope: !8, file: !1, line: 13, type: !11)
!43 = !DILocation(line: 13, column: 6, scope: !8)
!44 = !DILocalVariable(name: "d", scope: !8, file: !1, line: 14, type: !11)
!45 = !DILocation(line: 14, column: 6, scope: !8)
!46 = !DILocation(line: 14, column: 10, scope: !8)
!47 = !DILocation(line: 14, column: 14, scope: !8)
!48 = !DILocation(line: 14, column: 12, scope: !8)
!49 = !DILocation(line: 15, column: 9, scope: !8)
!50 = !DILocation(line: 15, column: 2, scope: !8)
