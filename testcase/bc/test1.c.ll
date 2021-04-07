; ModuleID = './testcase/bc/test1.c.ll'
source_filename = "./testcase/src/test1.c"
target datalayout = "e-m:o-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx10.16.0"

@source.initstr = internal global [25 x i8] c"select* From City ..\00\00\00\00\00", align 16, !dbg !0

; Function Attrs: noinline nounwind ssp uwtable
define i8* @source() #0 !dbg !2 {
entry:
  ret i8* getelementptr inbounds ([25 x i8], [25 x i8]* @source.initstr, i64 0, i64 0), !dbg !20
}

; Function Attrs: noinline nounwind ssp uwtable
define i8* @sink(i8* %s) #0 !dbg !21 {
entry:
  call void @llvm.dbg.value(metadata i8* %s, metadata !24, metadata !DIExpression()), !dbg !25
  ret i8* %s, !dbg !26
}

; Function Attrs: nounwind readnone speculatable willreturn
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: noinline nounwind ssp uwtable
define i32 @main() #0 !dbg !27 {
entry:
  %call = call i8* @source(), !dbg !31
  call void @llvm.dbg.value(metadata i8* %call, metadata !32, metadata !DIExpression()), !dbg !33
  %call1 = call i8* @sink(i8* %call), !dbg !34
  call void @llvm.dbg.value(metadata i8* %call1, metadata !35, metadata !DIExpression()), !dbg !33
  ret i32 0, !dbg !36
}

; Function Attrs: nounwind readnone speculatable willreturn
declare void @llvm.dbg.value(metadata, metadata, metadata) #1

attributes #0 = { noinline nounwind ssp uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+cx8,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone speculatable willreturn }

!llvm.dbg.cu = !{!8}
!llvm.module.flags = !{!15, !16, !17, !18}
!llvm.ident = !{!19}

!0 = !DIGlobalVariableExpression(var: !1, expr: !DIExpression())
!1 = distinct !DIGlobalVariable(name: "initstr", scope: !2, file: !3, line: 5, type: !12, isLocal: true, isDefinition: true)
!2 = distinct !DISubprogram(name: "source", scope: !3, file: !3, line: 3, type: !4, scopeLine: 3, spFlags: DISPFlagDefinition, unit: !8, retainedNodes: !10)
!3 = !DIFile(filename: "./testcase/src/test1.c", directory: "/Users/charles/UTS/SVF-all/guanqin-patch/SVF-example")
!4 = !DISubroutineType(types: !5)
!5 = !{!6}
!6 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !7, size: 64)
!7 = !DIBasicType(name: "char", size: 8, encoding: DW_ATE_signed_char)
!8 = distinct !DICompileUnit(language: DW_LANG_C99, file: !9, producer: "clang version 10.0.0 ", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !10, globals: !11, nameTableKind: None)
!9 = !DIFile(filename: "testcase/src/test1.c", directory: "/Users/charles/UTS/SVF-all/guanqin-patch/SVF-example")
!10 = !{}
!11 = !{!0}
!12 = !DICompositeType(tag: DW_TAG_array_type, baseType: !7, size: 200, elements: !13)
!13 = !{!14}
!14 = !DISubrange(count: 25)
!15 = !{i32 7, !"Dwarf Version", i32 4}
!16 = !{i32 2, !"Debug Info Version", i32 3}
!17 = !{i32 1, !"wchar_size", i32 4}
!18 = !{i32 7, !"PIC Level", i32 2}
!19 = !{!"clang version 10.0.0 "}
!20 = !DILocation(line: 6, column: 5, scope: !2)
!21 = distinct !DISubprogram(name: "sink", scope: !3, file: !3, line: 9, type: !22, scopeLine: 9, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !8, retainedNodes: !10)
!22 = !DISubroutineType(types: !23)
!23 = !{!6, !6}
!24 = !DILocalVariable(name: "s", arg: 1, scope: !21, file: !3, line: 9, type: !6)
!25 = !DILocation(line: 0, scope: !21)
!26 = !DILocation(line: 10, column: 5, scope: !21)
!27 = distinct !DISubprogram(name: "main", scope: !3, file: !3, line: 13, type: !28, scopeLine: 13, spFlags: DISPFlagDefinition, unit: !8, retainedNodes: !10)
!28 = !DISubroutineType(types: !29)
!29 = !{!30}
!30 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!31 = !DILocation(line: 14, column: 23, scope: !27)
!32 = !DILocalVariable(name: "injection", scope: !27, file: !3, line: 14, type: !6)
!33 = !DILocation(line: 0, scope: !27)
!34 = !DILocation(line: 15, column: 15, scope: !27)
!35 = !DILocalVariable(name: "s", scope: !27, file: !3, line: 15, type: !6)
!36 = !DILocation(line: 16, column: 5, scope: !27)
