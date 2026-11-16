
declare i32 @read()

declare void @print(i32)

define i32 @func(i32 %0) {
entryBB:
  %a = alloca i32, align 4
  %b = alloca i32, align 4
  %p = alloca i32, align 4
  %return = alloca i32, align 4
  store i32 %0, ptr %p, align 4
  store i32 10, ptr %a, align 4
  %1 = load i32, ptr %a, align 4
  %2 = load i32, ptr %p, align 4
  %3 = add i32 %1, %2
  store i32 %3, ptr %b, align 4
  %4 = load i32, ptr %b, align 4
  store i32 %4, ptr %return, align 4
  br label %retBB

retBB:                                            ; preds = %entryBB
  %5 = load i32, ptr %return, align 4
  ret i32 %5
}
