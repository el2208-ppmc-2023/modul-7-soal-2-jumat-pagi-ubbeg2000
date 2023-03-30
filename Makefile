main: main.c function_lib.c function_lib.h
	gcc -o main main.c function_lib.c

clean:
	rm ./main
