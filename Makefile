all: libparray.so tester
# nothing should go here

tester: tester.c libparray.so
	gcc -g -Wall -Wextra -Werror -Wno-unused tester.c -o tester -L. -lparray

libparray.so: parray.c
	gcc -g -c -fpic parray.c -Wall -Wextra -Werror
	gcc parray.o -shared -o libparray.so

clean:
	rm -f *.o *.so tester vgcore*
