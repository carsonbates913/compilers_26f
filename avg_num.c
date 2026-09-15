#include<stdio.h>

extern void print(int); // function to print a value
extern int read(); // function to read a value

int avg_num(int a){

  print("Select the number of inputs");
  int result;
  int running_sum;

  for(int i = 0; i < a; i++) {
    int x;
    x = read();
    running_sum = running_sum + x;
  }

  result = running_sum / a;

  return result;
}

int main(){
        int i = avg_num(4);
        printf("Return value of test: %d\n", i);
        return 0;
}
