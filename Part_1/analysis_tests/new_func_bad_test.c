extern void print(int);
extern int read();

int func(int i){
	int a;
  int b;
  int c;
	
	a = read();
  
	b = 5;
	
	while(a < i){
		a = a + b;
		print(b);
	}
  c = hello();
	return a;
}
