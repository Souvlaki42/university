all:
	gcc -I/usr/include/mpich-x86_64 -ggdb -Wall -Wextra fires.c -L/usr/lib64/mpich/lib -lmpi -o fires

run: all
	mpirun -np 11 ./fires