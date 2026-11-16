; ModuleID = 'ir_tests/p4_const_prop.c'
source_filename = "ir_tests/p4_const_prop.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @func(i32 noundef %i) #0 {
entry:
  %i.addr = alloca i32, align 4
  %a = alloca i32, align 4
  %b = alloca i32, align 4
  %c = alloca i32, align 4
  %d = alloca i32, align 4
  store i32 %i, ptr %i.addr, align 4
  store i32 10, ptr %a, align 4
  store i32 20, ptr %b, align 4
  %0 = load i32, ptr %a, align 4
  %add = add nsw i32 %0, 10
  store i32 %add, ptr %c, align 4
  store i32 5, ptr %a, align 4
  br label %while.cond

while.cond:                                       ; preds = %if.end, %entry
  %1 = load i32, ptr %a, align 4
  %2 = load i32, ptr %i.addr, align 4
  %cmp = icmp slt i32 %1, %2
  br i1 %cmp, label %while.body, label %while.end

while.body:                                       ; preds = %while.cond
  %3 = load i32, ptr %a, align 4
  %add1 = add nsw i32 %3, 1
  store i32 %add1, ptr %a, align 4
  %4 = load i32, ptr %a, align 4
  %5 = load i32, ptr %b, align 4
  %cmp2 = icmp sgt i32 %4, %5
  br i1 %cmp2, label %if.then, label %if.else

if.then:                                          ; preds = %while.body
  store i32 25, ptr %c, align 4
  br label %if.end

if.else:                                          ; preds = %while.body
  store i32 25, ptr %c, align 4
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  br label %while.cond, !llvm.loop !6

while.end:                                        ; preds = %while.cond
  %6 = load i32, ptr %a, align 4
  call void @print(i32 noundef %6)
  %7 = load i32, ptr %b, align 4
  call void @print(i32 noundef %7)
  %8 = load i32, ptr %c, align 4
  call void @print(i32 noundef %8)
  %9 = load i32, ptr %b, align 4
  %10 = load i32, ptr %c, align 4
  %add3 = add nsw i32 %9, %10
  ret i32 %add3
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
