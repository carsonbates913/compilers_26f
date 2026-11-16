
declare i32 @read()

declare void @print(i32)

define i32 @func(i32 %0) {
entryBB:
  %a = alloca i32, align 4
  %a2 = alloca i32, align 4
  %b = alloca i32, align 4
  %p = alloca i32, align 4
  %return = alloca i32, align 4
  store i32 %0, ptr %p, align 4
  store i32 0, ptr %a, align 4
  %1 = load i32, ptr %p, align 4
  %2 = icmp slt i32 %1, 0
  br i1 %2, label %trueBB, label %falseBB

retBB:                                            ; preds = %endBB
  %3 = load i32, ptr %return, align 4
  ret i32 %3

trueBB:                                           ; preds = %entryBB
  store i32 10, ptr %a, align 4
  br label %endBB

falseBB:                                          ; preds = %entryBB
  store i32 2, ptr %a2, align 4
  store i32 0, ptr %b, align 4
  br label %condBB

condBB:                                           ; preds = %trueBB1, %falseBB
  %4 = load i32, ptr %b, align 4
  %5 = load i32, ptr %p, align 4
  %6 = icmp slt i32 %4, %5
  br i1 %6, label %trueBB1, label %falseBB2

trueBB1:                                          ; preds = %condBB
  %7 = load i32, ptr %b, align 4
  %8 = load i32, ptr %a2, align 4
  %9 = add i32 %7, %8
  store i32 %9, ptr %b, align 4
  br label %condBB

falseBB2:                                         ; preds = %condBB
  br label %endBB

endBB:                                            ; preds = %falseBB2, %trueBB
  %10 = load i32, ptr %a, align 4
  %11 = load i32, ptr %b, align 4
  %12 = add i32 %10, %11
  store i32 %12, ptr %return, align 4
  br label %retBB
}
