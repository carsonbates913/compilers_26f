#include<stdio.h>

extern void print(int); // function to print a value
extern int read(); // function to read a value

int func(){

  if (a == 0) {
    return 0;
  }

  func(a - 1);

  for(int i = 0; i < a; i++) {
    print(0);
  }

  return 0;
}

int main(){
  print("How big would you like your triangle to be?");
  int i = func();
  printf("Return value of test: %d\n", i);
  return 0;
}
