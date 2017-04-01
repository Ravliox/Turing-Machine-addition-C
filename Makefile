build: main.c
	gcc -g -Wall main.c turing.c -o t
run:
	./t
debug:
	gdb t
clean:
	rm t tape.out
