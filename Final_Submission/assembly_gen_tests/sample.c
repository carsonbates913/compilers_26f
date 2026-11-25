extern void print(int);
extern int read();

int func(int n){
	int i;
	int sum;
	int a;
	int b;
	int c;
	int t;

	a = 2 + 3;
	b = a * 4;
	print(b);

	c = n + a;
	t = n + a;
	print(t);

	i = 0;
	sum = 0;
	while (i < n){
		int x;
		x = read();
		t = x * 2;
		if (t > 10){
			int a;
			a = x - 1;
			sum = sum + a;
		} else {
			sum = sum + t;
		}
		i = i + 1;
	}

	print(a);
	t = sum + c;
	return t;
}
