; ModuleID = 'ir_tests/example5.c'
source_filename = "ir_tests/example5.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @func() #0 {
entry:
  %width = alloca i32, align 4
  %length = alloca i32, align 4
  %area = alloca i32, align 4
  %perimeter = alloca i32, align 4
  %double_width = alloca i32, align 4
  %double_length = alloca i32, align 4
  %call = call i32 (...) @read()
  store i32 %call, ptr %width, align 4
  %call1 = call i32 (...) @read()
  store i32 %call1, ptr %length, align 4
  %0 = load i32, ptr %width, align 4
  %1 = load i32, ptr %length, align 4
  %mul = mul nsw i32 %0, %1
  store i32 %mul, ptr %area, align 4
  %2 = load i32, ptr %length, align 4
  %3 = load i32, ptr %length, align 4
  %add = add nsw i32 %2, %3
  store i32 %add, ptr %double_length, align 4
  %4 = load i32, ptr %width, align 4
  %5 = load i32, ptr %width, align 4
  %add2 = add nsw i32 %4, %5
  store i32 %add2, ptr %double_width, align 4
  %6 = load i32, ptr %double_length, align 4
  %7 = load i32, ptr %double_width, align 4
  %add3 = add nsw i32 %6, %7
  store i32 %add3, ptr %perimeter, align 4
  %8 = load i32, ptr %area, align 4
  call void @print(i32 noundef %8)
  %9 = load i32, ptr %perimeter, align 4
  call void @print(i32 noundef %9)
  ret i32 0
}

declare i32 @read(...) #1

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
