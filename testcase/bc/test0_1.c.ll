; ModuleID = './testcase/bc/test0_1.c.ll'
source_filename = "./testcase/src/test0_1.c"
target datalayout = "e-m:o-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx10.16.0"

; Function Attrs: noinline nounwind ssp uwtable
define i32 @source() #0 !dbg !8 {
entry:
  ret i32 1, !dbg !13
}

; Function Attrs: noinline nounwind ssp uwtable
define void @sink(i32* %s) #0 !dbg !14 {
entry:
  call void @llvm.dbg.value(metadata i32* %s, metadata !18, metadata !DIExpression()), !dbg !19
  ret void, !dbg !20
}

; Function Attrs: nounwind readnone speculatable willreturn
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: noinline nounwind ssp uwtable
define i32 @main() #0 !dbg !21 {
entry:
  %injection = alloca i32, align 4
  call void @llvm.dbg.declare(metadata i32* %injection, metadata !22, metadata !DIExpression()), !dbg !23
  %call = call i32 @source(), !dbg !24
  store i32 %call, i32* %injection, align 4, !dbg !23
  call void @sink(i32* %injection), !dbg !25
  ret i32 0, !dbg !26
}

; Function Attrs: nounwind readnone speculatable willreturn
declare void @llvm.dbg.value(metadata, metadata, metadata) #1

attributes #0 = { noinline nounwind ssp uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+cx8,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone speculatable willreturn }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!3, !4, !5, !6}
!llvm.ident = !{!7}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 10.0.0 ", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !2, nameTableKind: None)
!1 = !DIFile(filename: "testcase/src/test0_1.c", directory: "/Users/charles/UTS/SVF-all/guanqin-patch/SVF-example")
!2 = !{}
!3 = !{i32 7, !"Dwarf Version", i32 4}
!4 = !{i32 2, !"Debug Info Version", i32 3}
!5 = !{i32 1, !"wchar_size", i32 4}
!6 = !{i32 7, !"PIC Level", i32 2}
!7 = !{!"clang version 10.0.0 "}
!8 = distinct !DISubprogram(name: "source", scope: !9, file: !9, line: 3, type: !10, scopeLine: 3, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !2)
!9 = !DIFile(filename: "./testcase/src/test0_1.c", directory: "/Users/charles/UTS/SVF-all/guanqin-patch/SVF-example")
!10 = !DISubroutineType(types: !11)
!11 = !{!12}
!12 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!13 = !DILocation(line: 4, column: 5, scope: !8)
!14 = distinct !DISubprogram(name: "sink", scope: !9, file: !9, line: 7, type: !15, scopeLine: 7, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !2)
!15 = !DISubroutineType(types: !16)
!16 = !{null, !17}
!17 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !12, size: 64)
!18 = !DILocalVariable(name: "s", arg: 1, scope: !14, file: !9, line: 7, type: !17)
!19 = !DILocation(line: 0, scope: !14)
!20 = !DILocation(line: 8, column: 1, scope: !14)
!21 = distinct !DISubprogram(name: "main", scope: !9, file: !9, line: 10, type: !10, scopeLine: 10, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !2)
!22 = !DILocalVariable(name: "injection", scope: !21, file: !9, line: 11, type: !12)
!23 = !DILocation(line: 11, column: 9, scope: !21)
!24 = !DILocation(line: 11, column: 21, scope: !21)
!25 = !DILocation(line: 12, column: 5, scope: !21)
!26 = !DILocation(line: 13, column: 5, scope: !21)
