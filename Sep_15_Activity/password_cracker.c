extern void print(int);
extern int read();

int func(){
  int first_digit_password;
  int second_digit_password;
  int third_digit_password;
  int fourth_digit_password;
  int num_digits_guessed;

  first_digit_password = 8;
  second_digit_password = 3;
  third_digit_password = 2;
  fourth_digit_password = 9;

  num_digits_guessed = 0;

  while(num_digits_guessed < 4){
    int guess;

    if(num_digits_guessed == 1) {
      print(8);
    }
    if(num_digits_guessed == 2) {
      print(83);
    }
    if(num_digits_guessed == 3) {
      print(832);
    }

    guess = read();

    if(num_digits_guessed == 3){
      if(guess == 9){
        num_digits_guessed = 4;
        print(8329);
        return 8329;
      }
    }

    if(num_digits_guessed == 2){
      if(guess == 2) {
        num_digits_guessed = 3;
      }
    }

    if(num_digits_guessed == 1){
      if(guess == 3) {
        num_digits_guessed = 2;
      }
    }

    if(num_digits_guessed == 0){
      if(guess == 8) {
        num_digits_guessed = 1;
      }
    }
  }
  return 8329;
}
