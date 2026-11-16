target triple = "x86_64-pc-linux-gnu"

declare i32 @read()

declare void @print(i32)

define i32 @func(i32 %0) {
entryBB:
  %a = alloca i32, align 4
  %a2 = alloca i32, align 4
  %a3 = alloca i32, align 4
  %i = alloca i32, align 4
  %max = alloca i32, align 4
  %n = alloca i32, align 4
  %n2 = alloca i32, align 4
  %return = alloca i32, align 4
  store i32 %0, ptr %n, align 4
  store i32 0, ptr %i, align 4
  store i32 0, ptr %max, align 4
  br label %condBB

retBB:                                            ; preds = %falseBB
  %1 = load i32, ptr %return, align 4
  ret i32 %1

condBB:                                           ; preds = %falseBB4, %entryBB
  %2 = load i32, ptr %i, align 4
  %3 = load i32, ptr %n, align 4
  %4 = icmp slt i32 %2, %3
  br i1 %4, label %trueBB, label %falseBB

trueBB:                                           ; preds = %condBB
  %5 = call i32 @read()
  store i32 %5, ptr %a2, align 4
  %6 = load i32, ptr %a2, align 4
  %7 = load i32, ptr %max, align 4
  %8 = icmp sgt i32 %6, %7
  br i1 %8, label %trueBB1, label %falseBB2

falseBB:                                          ; preds = %condBB
  %9 = load i32, ptr %max, align 4
  store i32 %9, ptr %return, align 4
  br label %retBB

trueBB1:                                          ; preds = %trueBB
  %10 = load i32, ptr %a2, align 4
  store i32 %10, ptr %max, align 4
  br label %falseBB2

falseBB2:                                         ; preds = %trueBB1, %trueBB
  %11 = load i32, ptr %i, align 4
  %12 = add i32 %11, 1
  store i32 %12, ptr %i, align 4
  %13 = load i32, ptr %a2, align 4
  %14 = load i32, ptr %max, align 4
  %15 = icmp sgt i32 %13, %14
  br i1 %15, label %trueBB3, label %falseBB4

trueBB3:                                          ; preds = %falseBB2
  %16 = load i32, ptr %i, align 4
  %17 = load i32, ptr %a3, align 4
  %18 = add i32 %16, %17
  store i32 %18, ptr %i, align 4
  br label %falseBB4

falseBB4:                                         ; preds = %trueBB3, %falseBB2
  br label %condBB
}
