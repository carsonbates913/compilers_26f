target triple = "x86_64-pc-linux-gnu"

declare i32 @read()

declare void @print(i32)

define i32 @func(i32 %0) {
entryBB:
  %a = alloca i32, align 4
  %i = alloca i32, align 4
  %n = alloca i32, align 4
  %sum = alloca i32, align 4
  %return = alloca i32, align 4
  store i32 %0, ptr %n, align 4
  store i32 0, ptr %i, align 4
  store i32 0, ptr %sum, align 4
  br label %condBB

retBB:                                            ; preds = %falseBB
  %1 = load i32, ptr %return, align 4
  ret i32 %1

condBB:                                           ; preds = %trueBB, %entryBB
  %2 = load i32, ptr %i, align 4
  %3 = load i32, ptr %n, align 4
  %4 = icmp slt i32 %2, %3
  br i1 %4, label %trueBB, label %falseBB

trueBB:                                           ; preds = %condBB
  %5 = call i32 @read()
  store i32 %5, ptr %a, align 4
  %6 = load i32, ptr %sum, align 4
  %7 = load i32, ptr %a, align 4
  %8 = add i32 %6, %7
  store i32 %8, ptr %sum, align 4
  %9 = load i32, ptr %i, align 4
  %10 = add i32 %9, 1
  store i32 %10, ptr %i, align 4
  br label %condBB

falseBB:                                          ; preds = %condBB
  %11 = load i32, ptr %sum, align 4
  store i32 %11, ptr %return, align 4
  br label %retBB
}
