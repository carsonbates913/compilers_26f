extern void print(int);
extern int read();

int func(){

  int a;
  int result;
  int running_sum;
  int i;

  a = read();

  i = a;
  while(i > 0) {
    int x;
    
    x = read();
    running_sum = running_sum + x;
    i = i - 1;
  }

  result = running_sum / a;

  return result;
}
