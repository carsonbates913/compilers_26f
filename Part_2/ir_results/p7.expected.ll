; ModuleID = 'ir_tests/p7.c'
source_filename = "ir_tests/p7.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @func(i32 noundef %n) #0 {
entry:
  %n.addr = alloca i32, align 4
  %max = alloca i32, align 4
  %i = alloca i32, align 4
  %a = alloca i32, align 4
  %a1 = alloca i32, align 4
  %a5 = alloca i32, align 4
  %n6 = alloca i32, align 4
  store i32 %n, ptr %n.addr, align 4
  store i32 0, ptr %i, align 4
  store i32 0, ptr %max, align 4
  br label %while.cond

while.cond:                                       ; preds = %if.end8, %entry
  %0 = load i32, ptr %i, align 4
  %1 = load i32, ptr %n.addr, align 4
  %cmp = icmp slt i32 %0, %1
  br i1 %cmp, label %while.body, label %while.end

while.body:                                       ; preds = %while.cond
  %call = call i32 (...) @read()
  store i32 %call, ptr %a1, align 4
  %2 = load i32, ptr %a1, align 4
  %3 = load i32, ptr %max, align 4
  %cmp2 = icmp sgt i32 %2, %3
  br i1 %cmp2, label %if.then, label %if.end

if.then:                                          ; preds = %while.body
  %4 = load i32, ptr %a1, align 4
  store i32 %4, ptr %max, align 4
  br label %if.end

if.end:                                           ; preds = %if.then, %while.body
  %5 = load i32, ptr %i, align 4
  %add = add nsw i32 %5, 1
  store i32 %add, ptr %i, align 4
  %6 = load i32, ptr %a1, align 4
  %7 = load i32, ptr %max, align 4
  %cmp3 = icmp sgt i32 %6, %7
  br i1 %cmp3, label %if.then4, label %if.end8

if.then4:                                         ; preds = %if.end
  %8 = load i32, ptr %i, align 4
  %9 = load i32, ptr %a5, align 4
  %add7 = add nsw i32 %8, %9
  store i32 %add7, ptr %i, align 4
  br label %if.end8

if.end8:                                          ; preds = %if.then4, %if.end
  br label %while.cond, !llvm.loop !6

while.end:                                        ; preds = %while.cond
  %10 = load i32, ptr %max, align 4
  ret i32 %10
}

declare i32 @read(...) #1

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
