extern void print(int);
extern int read();

int func(){

  int width;
  int length;
  int area;
  int perimeter;
  int double_width;
  int double_length;

  width = read();
  length = read();

  area = width * length;

  double_length = length + length;
  double_width = width + width;
  perimeter = double_length + double_width;

  print(area);
  print(perimeter);

  return 0;
}
