; ModuleID = 'ir_tests/example3.c'
source_filename = "ir_tests/example3.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @func(i32 noundef %k) #0 {
entry:
  %retval = alloca i32, align 4
  %k.addr = alloca i32, align 4
  %first_digit_password = alloca i32, align 4
  %second_digit_password = alloca i32, align 4
  %third_digit_password = alloca i32, align 4
  %fourth_digit_password = alloca i32, align 4
  %num_digits_guessed = alloca i32, align 4
  %guess = alloca i32, align 4
  store i32 %k, ptr %k.addr, align 4
  store i32 8, ptr %first_digit_password, align 4
  store i32 3, ptr %second_digit_password, align 4
  store i32 2, ptr %third_digit_password, align 4
  store i32 9, ptr %fourth_digit_password, align 4
  store i32 0, ptr %num_digits_guessed, align 4
  br label %while.cond

while.cond:                                       ; preds = %if.end31, %entry
  %0 = load i32, ptr %num_digits_guessed, align 4
  %cmp = icmp slt i32 %0, 4
  br i1 %cmp, label %while.body, label %while.end

while.body:                                       ; preds = %while.cond
  %1 = load i32, ptr %num_digits_guessed, align 4
  %cmp1 = icmp eq i32 %1, 1
  br i1 %cmp1, label %if.then, label %if.end

if.then:                                          ; preds = %while.body
  call void @print(i32 noundef 8)
  br label %if.end

if.end:                                           ; preds = %if.then, %while.body
  %2 = load i32, ptr %num_digits_guessed, align 4
  %cmp2 = icmp eq i32 %2, 2
  br i1 %cmp2, label %if.then3, label %if.end4

if.then3:                                         ; preds = %if.end
  call void @print(i32 noundef 83)
  br label %if.end4

if.end4:                                          ; preds = %if.then3, %if.end
  %3 = load i32, ptr %num_digits_guessed, align 4
  %cmp5 = icmp eq i32 %3, 3
  br i1 %cmp5, label %if.then6, label %if.end7

if.then6:                                         ; preds = %if.end4
  call void @print(i32 noundef 832)
  br label %if.end7

if.end7:                                          ; preds = %if.then6, %if.end4
  %call = call i32 (...) @read()
  store i32 %call, ptr %guess, align 4
  %4 = load i32, ptr %num_digits_guessed, align 4
  %cmp8 = icmp eq i32 %4, 3
  br i1 %cmp8, label %if.then9, label %if.end13

if.then9:                                         ; preds = %if.end7
  %5 = load i32, ptr %guess, align 4
  %cmp10 = icmp eq i32 %5, 9
  br i1 %cmp10, label %if.then11, label %if.end12

if.then11:                                        ; preds = %if.then9
  store i32 4, ptr %num_digits_guessed, align 4
  call void @print(i32 noundef 8329)
  store i32 8329, ptr %retval, align 4
  br label %return

if.end12:                                         ; preds = %if.then9
  br label %if.end13

if.end13:                                         ; preds = %if.end12, %if.end7
  %6 = load i32, ptr %num_digits_guessed, align 4
  %cmp14 = icmp eq i32 %6, 2
  br i1 %cmp14, label %if.then15, label %if.end19

if.then15:                                        ; preds = %if.end13
  %7 = load i32, ptr %guess, align 4
  %cmp16 = icmp eq i32 %7, 2
  br i1 %cmp16, label %if.then17, label %if.end18

if.then17:                                        ; preds = %if.then15
  store i32 3, ptr %num_digits_guessed, align 4
  br label %if.end18

if.end18:                                         ; preds = %if.then17, %if.then15
  br label %if.end19

if.end19:                                         ; preds = %if.end18, %if.end13
  %8 = load i32, ptr %num_digits_guessed, align 4
  %cmp20 = icmp eq i32 %8, 1
  br i1 %cmp20, label %if.then21, label %if.end25

if.then21:                                        ; preds = %if.end19
  %9 = load i32, ptr %guess, align 4
  %cmp22 = icmp eq i32 %9, 3
  br i1 %cmp22, label %if.then23, label %if.end24

if.then23:                                        ; preds = %if.then21
  store i32 2, ptr %num_digits_guessed, align 4
  br label %if.end24

if.end24:                                         ; preds = %if.then23, %if.then21
  br label %if.end25

if.end25:                                         ; preds = %if.end24, %if.end19
  %10 = load i32, ptr %num_digits_guessed, align 4
  %cmp26 = icmp eq i32 %10, 0
  br i1 %cmp26, label %if.then27, label %if.end31

if.then27:                                        ; preds = %if.end25
  %11 = load i32, ptr %guess, align 4
  %cmp28 = icmp eq i32 %11, 8
  br i1 %cmp28, label %if.then29, label %if.end30

if.then29:                                        ; preds = %if.then27
  store i32 1, ptr %num_digits_guessed, align 4
  br label %if.end30

if.end30:                                         ; preds = %if.then29, %if.then27
  br label %if.end31

if.end31:                                         ; preds = %if.end30, %if.end25
  br label %while.cond, !llvm.loop !6

while.end:                                        ; preds = %while.cond
  store i32 8329, ptr %retval, align 4
  br label %return

return:                                           ; preds = %while.end, %if.then11
  %12 = load i32, ptr %retval, align 4
  ret i32 %12
}

declare void @print(i32 noundef) #1

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
