; ModuleID = './testcase/bc/test5.c.ll'
source_filename = "./testcase/src/test5.c"
target datalayout = "e-m:o-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx10.16.0"

; Function Attrs: noinline nounwind ssp uwtable
define i32 @main() #0 !dbg !8 {
entry:
  %a = alloca i32, align 4
  %call = call i32 (...) @source(), !dbg !13
  call void @llvm.dbg.value(metadata i32 %call, metadata !14, metadata !DIExpression()), !dbg !15
  call void @llvm.dbg.declare(metadata i32* %a, metadata !16, metadata !DIExpression()), !dbg !17
  store i32 %call, i32* %a, align 4, !dbg !17
  %add = add nsw i32 %call, 5, !dbg !18
  store i32 %add, i32* %a, align 4, !dbg !19
  call void @sink(i32* %a), !dbg !20
  ret i32 0, !dbg !21
}

; Function Attrs: nounwind readnone speculatable willreturn
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare i32 @source(...) #2

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
!1 = !DIFile(filename: "testcase/src/test5.c", directory: "/Users/charles/UTS/SVF-all/guanqin-patch/SVF-example")
!2 = !{}
!3 = !{i32 7, !"Dwarf Version", i32 4}
!4 = !{i32 2, !"Debug Info Version", i32 3}
!5 = !{i32 1, !"wchar_size", i32 4}
!6 = !{i32 7, !"PIC Level", i32 2}
!7 = !{!"clang version 10.0.0 "}
!8 = distinct !DISubprogram(name: "main", scope: !9, file: !9, line: 4, type: !10, scopeLine: 4, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !2)
!9 = !DIFile(filename: "./testcase/src/test5.c", directory: "/Users/charles/UTS/SVF-all/guanqin-patch/SVF-example")
!10 = !DISubroutineType(types: !11)
!11 = !{!12}
!12 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!13 = !DILocation(line: 5, column: 19, scope: !8)
!14 = !DILocalVariable(name: "num", scope: !8, file: !9, line: 5, type: !12)
!15 = !DILocation(line: 0, scope: !8)
!16 = !DILocalVariable(name: "a", scope: !8, file: !9, line: 6, type: !12)
!17 = !DILocation(line: 6, column: 13, scope: !8)
!18 = !DILocation(line: 7, column: 17, scope: !8)
!19 = !DILocation(line: 7, column: 11, scope: !8)
!20 = !DILocation(line: 8, column: 9, scope: !8)
!21 = !DILocation(line: 10, column: 9, scope: !8)
