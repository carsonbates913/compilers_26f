filename = lexfile

$(filename).out: $(filename).l
	lex $(filename).l
	gcc -g lex.yy.c -o $(filename).out

clean:
	rm -rf $(filename).out lex.yy.c