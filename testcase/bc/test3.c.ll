; ModuleID = './testcase/bc/test3.c.ll'
source_filename = "./testcase/src/test3.c"
target datalayout = "e-m:o-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx10.16.0"

; Function Attrs: noinline nounwind ssp uwtable
define i32 @source(i32 %s) #0 !dbg !8 {
entry:
  call void @llvm.dbg.value(metadata i32 %s, metadata !13, metadata !DIExpression()), !dbg !14
  %cmp = icmp sgt i32 %s, 1, !dbg !15
  br i1 %cmp, label %if.then, label %if.else, !dbg !17

if.then:                                          ; preds = %entry
  %cmp1 = icmp sgt i32 %s, 2, !dbg !18
  br i1 %cmp1, label %if.then2, label %if.end, !dbg !21

if.then2:                                         ; preds = %if.then
  br label %return, !dbg !22

if.end:                                           ; preds = %if.then
  br label %return, !dbg !24

if.else:                                          ; preds = %entry
  %cmp3 = icmp slt i32 %s, -1, !dbg !25
  br i1 %cmp3, label %if.then4, label %if.end5, !dbg !28

if.then4:                                         ; preds = %if.else
  br label %return, !dbg !29

if.end5:                                          ; preds = %if.else
  br label %return, !dbg !31

return:                                           ; preds = %if.end5, %if.then4, %if.end, %if.then2
  %retval.0 = phi i32 [ 2, %if.then2 ], [ 1, %if.end ], [ -1, %if.then4 ], [ 0, %if.end5 ], !dbg !32
  ret i32 %retval.0, !dbg !33
}

; Function Attrs: nounwind readnone speculatable willreturn
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: noinline nounwind ssp uwtable
define i32 @main() #0 !dbg !34 {
entry:
  %num = alloca i32, align 4
  call void @llvm.dbg.declare(metadata i32* %num, metadata !37, metadata !DIExpression()), !dbg !38
  %call = call i32 @source(i32 1), !dbg !39
  store i32 %call, i32* %num, align 4, !dbg !38
  call void @sink(i32* %num), !dbg !40
  ret i32 0, !dbg !41
}

declare void @sink(i32*) #2

; Function Attrs: nounwind readnone speculatable willreturn
declare void @llvm.dbg.value(metadata, metadata, metadata) #1

attributes #0 = { noinline nounwind ssp uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+cx8,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone speculatable willreturn }
attributes #2 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+cx8,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!3, !4, !5, !6}
!llvm.ident = !{!7}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 10.0.0 ", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !2, nameTableKind: None)
!1 = !DIFile(filename: "testcase/src/test3.c", directory: "/Users/charles/UTS/SVF-all/guanqin-patch/SVF-example")
!2 = !{}
!3 = !{i32 7, !"Dwarf Version", i32 4}
!4 = !{i32 2, !"Debug Info Version", i32 3}
!5 = !{i32 1, !"wchar_size", i32 4}
!6 = !{i32 7, !"PIC Level", i32 2}
!7 = !{!"clang version 10.0.0 "}
!8 = distinct !DISubprogram(name: "source", scope: !9, file: !9, line: 3, type: !10, scopeLine: 3, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !2)
!9 = !DIFile(filename: "./testcase/src/test3.c", directory: "/Users/charles/UTS/SVF-all/guanqin-patch/SVF-example")
!10 = !DISubroutineType(types: !11)
!11 = !{!12, !12}
!12 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!13 = !DILocalVariable(name: "s", arg: 1, scope: !8, file: !9, line: 3, type: !12)
!14 = !DILocation(line: 0, scope: !8)
!15 = !DILocation(line: 4, column: 12, scope: !16)
!16 = distinct !DILexicalBlock(scope: !8, file: !9, line: 4, column: 10)
!17 = !DILocation(line: 4, column: 10, scope: !8)
!18 = !DILocation(line: 5, column: 16, scope: !19)
!19 = distinct !DILexicalBlock(scope: !20, file: !9, line: 5, column: 14)
!20 = distinct !DILexicalBlock(scope: !16, file: !9, line: 4, column: 17)
!21 = !DILocation(line: 5, column: 14, scope: !20)
!22 = !DILocation(line: 6, column: 13, scope: !23)
!23 = distinct !DILexicalBlock(scope: !19, file: !9, line: 5, column: 20)
!24 = !DILocation(line: 8, column: 9, scope: !20)
!25 = !DILocation(line: 10, column: 16, scope: !26)
!26 = distinct !DILexicalBlock(scope: !27, file: !9, line: 10, column: 14)
!27 = distinct !DILexicalBlock(scope: !16, file: !9, line: 9, column: 10)
!28 = !DILocation(line: 10, column: 14, scope: !27)
!29 = !DILocation(line: 11, column: 13, scope: !30)
!30 = distinct !DILexicalBlock(scope: !26, file: !9, line: 10, column: 22)
!31 = !DILocation(line: 13, column: 9, scope: !27)
!32 = !DILocation(line: 0, scope: !16)
!33 = !DILocation(line: 15, column: 1, scope: !8)
!34 = distinct !DISubprogram(name: "main", scope: !9, file: !9, line: 16, type: !35, scopeLine: 16, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !2)
!35 = !DISubroutineType(types: !36)
!36 = !{!12}
!37 = !DILocalVariable(name: "num", scope: !34, file: !9, line: 17, type: !12)
!38 = !DILocation(line: 17, column: 13, scope: !34)
!39 = !DILocation(line: 17, column: 19, scope: !34)
!40 = !DILocation(line: 18, column: 9, scope: !34)
!41 = !DILocation(line: 19, column: 9, scope: !34)
