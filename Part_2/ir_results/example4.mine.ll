target triple = "x86_64-pc-linux-gnu"

declare i32 @read()

declare void @print(i32)

define i32 @func(i32 %0) {
entryBB:
  %i = alloca i32, align 4
  %new_size = alloca i32, align 4
  %running_product = alloca i32, align 4
  %size = alloca i32, align 4
  %return = alloca i32, align 4
  store i32 %0, ptr %size, align 4
  %1 = load i32, ptr %size, align 4
  %2 = icmp eq i32 %1, 0
  br i1 %2, label %trueBB, label %falseBB

retBB:                                            ; preds = %falseBB2, %trueBB
  %3 = load i32, ptr %return, align 4
  ret i32 %3

trueBB:                                           ; preds = %entryBB
  call void @print(i32 1)
  store i32 0, ptr %return, align 4
  br label %retBB

falseBB:                                          ; preds = %entryBB
  %4 = load i32, ptr %size, align 4
  %5 = sub i32 %4, 1
  store i32 %5, ptr %new_size, align 4
  %6 = load i32, ptr %new_size, align 4
  %7 = call i32 @func(i32 %6)
  store i32 1, ptr %running_product, align 4
  %8 = load i32, ptr %size, align 4
  %9 = add i32 %8, 0
  store i32 %9, ptr %i, align 4
  br label %condBB

condBB:                                           ; preds = %trueBB1, %falseBB
  %10 = load i32, ptr %i, align 4
  %11 = icmp sgt i32 %10, 0
  br i1 %11, label %trueBB1, label %falseBB2

trueBB1:                                          ; preds = %condBB
  %12 = load i32, ptr %running_product, align 4
  %13 = mul i32 %12, 10
  store i32 %13, ptr %running_product, align 4
  %14 = load i32, ptr %i, align 4
  %15 = sub i32 %14, 1
  store i32 %15, ptr %i, align 4
  br label %condBB

falseBB2:                                         ; preds = %condBB
  %16 = load i32, ptr %running_product, align 4
  call void @print(i32 %16)
  store i32 0, ptr %return, align 4
  br label %retBB
}
