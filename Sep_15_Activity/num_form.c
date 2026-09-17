extern void print(int);
extern int read();

int func(){

  int question_answered;
  int highest_num;
  int num_1;
  int num_2;
  int num_3;
  int num_4;
  int num_5;
  int num_6;
  int i; 

  num_1 = 0;
  num_2 = 0;
  num_3 = 0;
  num_4 = 0;
  num_5 = 0;
  num_6 = 0;

  i = 6;
  while(i > 0) {
    question_answered = 0;

    while(question_answered < 1) {
      int choice;
      choice = read();
      if(choice == 1) {
        num_1 = num_1 + 1;
        question_answered = 1;
      }
      if(choice == 2) {
        num_2 = num_2 + 1;
        question_answered = 1;
      }
      if(choice == 3) {
        num_3 = num_3 + 1;
        question_answered = 1;
      }
      if(choice == 4) {
        num_4 = num_4 + 1;
        question_answered = 1;
      }
      if(choice == 5) {
        num_5 = num_5 + 1;
        question_answered = 1;
      }
      if(choice == 6) {
        num_6 = num_6 + 1;
        question_answered = 1;
      }
      if(choice < 1){
        print(0);
      }
      if(choice > 6){
        print(0);
      }
    }
    i = i -1;
  }

  highest_num = num_1 + 0;
  if(num_2 > highest_num) {
    highest_num = num_2 + 0;
  }
  if(num_3 > highest_num) {
    highest_num = num_3 + 0;
  }
  if(num_4 > highest_num) {
    highest_num = num_4 + 0;
  }
  if(num_5 > highest_num) {
    highest_num = num_5 + 0;
  }
  if(num_6 > highest_num) {
    highest_num = num_6 + 0;
  }

  print(1010101);

  if(highest_num == num_1) {
    print(1);
    return 1;
  }
  if(highest_num == num_2) {
    print(2);
    return 2;
  }
  if(highest_num == num_3) {
    print(3);
    return 3;
  }
  if(highest_num == num_4) {
    print(4);
    return 4;
  }
  if(highest_num == num_5) {
    print(5);
    return 5;
  }
  if(highest_num == num_6) {
    print(6);
    return 6;
  }

  return 0;
}
