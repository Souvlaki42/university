#!/usr/bin/env bash

function link-stack() {
  gcc -Wall -Wextra -c libStack.c -o libStack.o
  ar rcs libStack.a libStack.o
}

link-stack || exit 1
gcc -Wall -Wextra -o main main.c -L./ -l:libStack.a -I./
./main