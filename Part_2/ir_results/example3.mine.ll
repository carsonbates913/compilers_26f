target triple = "x86_64-pc-linux-gnu"

declare i32 @read()

declare void @print(i32)

define i32 @func(i32 %0) {
entryBB:
  %first_digit_password = alloca i32, align 4
  %fourth_digit_password = alloca i32, align 4
  %guess = alloca i32, align 4
  %k = alloca i32, align 4
  %num_digits_guessed = alloca i32, align 4
  %second_digit_password = alloca i32, align 4
  %third_digit_password = alloca i32, align 4
  %return = alloca i32, align 4
  store i32 %0, ptr %k, align 4
  store i32 8, ptr %first_digit_password, align 4
  store i32 3, ptr %second_digit_password, align 4
  store i32 2, ptr %third_digit_password, align 4
  store i32 9, ptr %fourth_digit_password, align 4
  store i32 0, ptr %num_digits_guessed, align 4
  br label %condBB

retBB:                                            ; preds = %falseBB, %trueBB9
  %1 = load i32, ptr %return, align 4
  ret i32 %1

condBB:                                           ; preds = %falseBB20, %entryBB
  %2 = load i32, ptr %num_digits_guessed, align 4
  %3 = icmp slt i32 %2, 4
  br i1 %3, label %trueBB, label %falseBB

trueBB:                                           ; preds = %condBB
  %4 = load i32, ptr %num_digits_guessed, align 4
  %5 = icmp eq i32 %4, 1
  br i1 %5, label %trueBB1, label %falseBB2

falseBB:                                          ; preds = %condBB
  store i32 8329, ptr %return, align 4
  br label %retBB

trueBB1:                                          ; preds = %trueBB
  call void @print(i32 8)
  br label %falseBB2

falseBB2:                                         ; preds = %trueBB1, %trueBB
  %6 = load i32, ptr %num_digits_guessed, align 4
  %7 = icmp eq i32 %6, 2
  br i1 %7, label %trueBB3, label %falseBB4

trueBB3:                                          ; preds = %falseBB2
  call void @print(i32 83)
  br label %falseBB4

falseBB4:                                         ; preds = %trueBB3, %falseBB2
  %8 = load i32, ptr %num_digits_guessed, align 4
  %9 = icmp eq i32 %8, 3
  br i1 %9, label %trueBB5, label %falseBB6

trueBB5:                                          ; preds = %falseBB4
  call void @print(i32 832)
  br label %falseBB6

falseBB6:                                         ; preds = %trueBB5, %falseBB4
  %10 = call i32 @read()
  store i32 %10, ptr %guess, align 4
  %11 = load i32, ptr %num_digits_guessed, align 4
  %12 = icmp eq i32 %11, 3
  br i1 %12, label %trueBB7, label %falseBB8

trueBB7:                                          ; preds = %falseBB6
  %13 = load i32, ptr %guess, align 4
  %14 = icmp eq i32 %13, 9
  br i1 %14, label %trueBB9, label %falseBB10

falseBB8:                                         ; preds = %falseBB10, %falseBB6
  %15 = load i32, ptr %num_digits_guessed, align 4
  %16 = icmp eq i32 %15, 2
  br i1 %16, label %trueBB11, label %falseBB12

trueBB9:                                          ; preds = %trueBB7
  store i32 4, ptr %num_digits_guessed, align 4
  call void @print(i32 8329)
  store i32 8329, ptr %return, align 4
  br label %retBB

falseBB10:                                        ; preds = %trueBB7
  br label %falseBB8

trueBB11:                                         ; preds = %falseBB8
  %17 = load i32, ptr %guess, align 4
  %18 = icmp eq i32 %17, 2
  br i1 %18, label %trueBB13, label %falseBB14

falseBB12:                                        ; preds = %falseBB14, %falseBB8
  %19 = load i32, ptr %num_digits_guessed, align 4
  %20 = icmp eq i32 %19, 1
  br i1 %20, label %trueBB15, label %falseBB16

trueBB13:                                         ; preds = %trueBB11
  store i32 3, ptr %num_digits_guessed, align 4
  br label %falseBB14

falseBB14:                                        ; preds = %trueBB13, %trueBB11
  br label %falseBB12

trueBB15:                                         ; preds = %falseBB12
  %21 = load i32, ptr %guess, align 4
  %22 = icmp eq i32 %21, 3
  br i1 %22, label %trueBB17, label %falseBB18

falseBB16:                                        ; preds = %falseBB18, %falseBB12
  %23 = load i32, ptr %num_digits_guessed, align 4
  %24 = icmp eq i32 %23, 0
  br i1 %24, label %trueBB19, label %falseBB20

trueBB17:                                         ; preds = %trueBB15
  store i32 2, ptr %num_digits_guessed, align 4
  br label %falseBB18

falseBB18:                                        ; preds = %trueBB17, %trueBB15
  br label %falseBB16

trueBB19:                                         ; preds = %falseBB16
  %25 = load i32, ptr %guess, align 4
  %26 = icmp eq i32 %25, 8
  br i1 %26, label %trueBB21, label %falseBB22

falseBB20:                                        ; preds = %falseBB22, %falseBB16
  br label %condBB

trueBB21:                                         ; preds = %trueBB19
  store i32 1, ptr %num_digits_guessed, align 4
  br label %falseBB22

falseBB22:                                        ; preds = %trueBB21, %trueBB19
  br label %falseBB20
}
