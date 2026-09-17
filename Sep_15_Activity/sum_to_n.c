extern void print(int);
extern int read();

int func(){

  int n;
  int n_1;
  int numerator;
  int result;

  n = read();

  n_1 = n + 1;
  numerator = n_1 * n;
  result = numerator / 2;

  print(result);

  return result;
}
