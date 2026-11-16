
declare i32 @read()

declare void @print(i32)

define i32 @func(i32 %0) {
entryBB:
  %a = alloca i32, align 4
  %k = alloca i32, align 4
  %result = alloca i32, align 4
  %return = alloca i32, align 4
  store i32 %0, ptr %k, align 4
  store i32 2, ptr %a, align 4
  %1 = load i32, ptr %a, align 4
  store i32 %1, ptr %result, align 4
  %2 = load i32, ptr %result, align 4
  store i32 %2, ptr %return, align 4
  br label %retBB

retBB:                                            ; preds = %entryBB
  %3 = load i32, ptr %return, align 4
  ret i32 %3
}
