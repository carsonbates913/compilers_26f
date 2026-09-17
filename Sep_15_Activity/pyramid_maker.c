extern void print(int);
extern int read();

int func(int size){

  int new_size;
  int i;
  int running_product;

  if (size == 0) {
    print(1);
    return 0; 
  }

  new_size = size - 1;

  func(new_size);


  running_product = 1;
  i = size + 0;
  while(i > 0) {
    running_product = running_product * 10;
    i = i - 1;
  }
  print(running_product);

  return 0;
}
