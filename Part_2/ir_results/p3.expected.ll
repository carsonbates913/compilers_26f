; ModuleID = 'ir_tests/p3.c'
source_filename = "ir_tests/p3.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @func(i32 noundef %n) #0 {
entry:
  %n.addr = alloca i32, align 4
  %a = alloca i32, align 4
  %b = alloca i32, align 4
  %i = alloca i32, align 4
  %t = alloca i32, align 4
  store i32 %n, ptr %n.addr, align 4
  store i32 1, ptr %a, align 4
  store i32 1, ptr %b, align 4
  store i32 0, ptr %i, align 4
  br label %while.cond

while.cond:                                       ; preds = %while.body, %entry
  %0 = load i32, ptr %i, align 4
  %1 = load i32, ptr %n.addr, align 4
  %cmp = icmp slt i32 %0, %1
  br i1 %cmp, label %while.body, label %while.end

while.body:                                       ; preds = %while.cond
  %2 = load i32, ptr %a, align 4
  call void @print(i32 noundef %2)
  %3 = load i32, ptr %i, align 4
  %add = add nsw i32 %3, 1
  store i32 %add, ptr %i, align 4
  %4 = load i32, ptr %a, align 4
  %5 = load i32, ptr %b, align 4
  %add1 = add nsw i32 %4, %5
  store i32 %add1, ptr %t, align 4
  %6 = load i32, ptr %b, align 4
  store i32 %6, ptr %a, align 4
  %7 = load i32, ptr %t, align 4
  store i32 %7, ptr %b, align 4
  br label %while.cond, !llvm.loop !6

while.end:                                        ; preds = %while.cond
  %8 = load i32, ptr %i, align 4
  ret i32 %8
}

declare void @print(i32 noundef) #1

attributes #0 = { noinline nounwind uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 8, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 2}
!4 = !{i32 7, !"frame-pointer", i32 2}
!5 = !{!"Homebrew clang version 21.1.8"}
!6 = distinct !{!6, !7}
!7 = !{!"llvm.loop.mustprogress"}
