; ModuleID = './testcase/bc/power3A.c.ll'
source_filename = "./testcase/src/power3A.c"
target datalayout = "e-m:o-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx10.16.0"

; Function Attrs: noinline nounwind ssp uwtable
define i32 @power3_A(i32 %in) #0 !dbg !8 {
entry:
  call void @llvm.dbg.value(metadata i32 %in, metadata !13, metadata !DIExpression()), !dbg !14
  call void @llvm.dbg.value(metadata i32 %in, metadata !15, metadata !DIExpression()), !dbg !14
  call void @llvm.dbg.value(metadata i32 0, metadata !16, metadata !DIExpression()), !dbg !14
  br label %for.cond, !dbg !17

for.cond:                                         ; preds = %for.inc, %entry
  %i.0 = phi i32 [ 0, %entry ], [ %inc, %for.inc ], !dbg !19
  %out_a.0 = phi i32 [ %in, %entry ], [ %mul, %for.inc ], !dbg !14
  call void @llvm.dbg.value(metadata i32 %out_a.0, metadata !15, metadata !DIExpression()), !dbg !14
  call void @llvm.dbg.value(metadata i32 %i.0, metadata !16, metadata !DIExpression()), !dbg !14
  %cmp = icmp slt i32 %i.0, 2, !dbg !20
  br i1 %cmp, label %for.body, label %for.end, !dbg !22

for.body:                                         ; preds = %for.cond
  %mul = mul nsw i32 %out_a.0, %in, !dbg !23
  call void @llvm.dbg.value(metadata i32 %mul, metadata !15, metadata !DIExpression()), !dbg !14
  br label %for.inc, !dbg !24

for.inc:                                          ; preds = %for.body
  %inc = add nsw i32 %i.0, 1, !dbg !25
  call void @llvm.dbg.value(metadata i32 %inc, metadata !16, metadata !DIExpression()), !dbg !14
  br label %for.cond, !dbg !26, !llvm.loop !27

for.end:                                          ; preds = %for.cond
  ret i32 %out_a.0, !dbg !29
}

; Function Attrs: nounwind readnone speculatable willreturn
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind readnone speculatable willreturn
declare void @llvm.dbg.value(metadata, metadata, metadata) #1

attributes #0 = { noinline nounwind ssp uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+cx8,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone speculatable willreturn }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!3, !4, !5, !6}
!llvm.ident = !{!7}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 10.0.0 ", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !2, nameTableKind: None)
!1 = !DIFile(filename: "testcase/src/power3A.c", directory: "/Users/charles/UTS/SVF-all/guanqin-patch/SVF-example")
!2 = !{}
!3 = !{i32 7, !"Dwarf Version", i32 4}
!4 = !{i32 2, !"Debug Info Version", i32 3}
!5 = !{i32 1, !"wchar_size", i32 4}
!6 = !{i32 7, !"PIC Level", i32 2}
!7 = !{!"clang version 10.0.0 "}
!8 = distinct !DISubprogram(name: "power3_A", scope: !9, file: !9, line: 1, type: !10, scopeLine: 1, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !2)
!9 = !DIFile(filename: "./testcase/src/power3A.c", directory: "/Users/charles/UTS/SVF-all/guanqin-patch/SVF-example")
!10 = !DISubroutineType(types: !11)
!11 = !{!12, !12}
!12 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!13 = !DILocalVariable(name: "in", arg: 1, scope: !8, file: !9, line: 1, type: !12)
!14 = !DILocation(line: 0, scope: !8)
!15 = !DILocalVariable(name: "out_a", scope: !8, file: !9, line: 2, type: !12)
!16 = !DILocalVariable(name: "i", scope: !8, file: !9, line: 2, type: !12)
!17 = !DILocation(line: 4, column: 8, scope: !18)
!18 = distinct !DILexicalBlock(scope: !8, file: !9, line: 4, column: 3)
!19 = !DILocation(line: 0, scope: !18)
!20 = !DILocation(line: 4, column: 17, scope: !21)
!21 = distinct !DILexicalBlock(scope: !18, file: !9, line: 4, column: 3)
!22 = !DILocation(line: 4, column: 3, scope: !18)
!23 = !DILocation(line: 5, column: 19, scope: !21)
!24 = !DILocation(line: 5, column: 5, scope: !21)
!25 = !DILocation(line: 4, column: 23, scope: !21)
!26 = !DILocation(line: 4, column: 3, scope: !21)
!27 = distinct !{!27, !22, !28}
!28 = !DILocation(line: 5, column: 21, scope: !18)
!29 = !DILocation(line: 6, column: 3, scope: !8)
