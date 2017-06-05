CC=clang # C compiler
CPP=c++  # C++ compiler

all: dirs libs arr char class int struct

dirs:
	@mkdir -p lib
	@mkdir -p bin

libs:
	$(CC) -c -o tree.o tree.c -fPIC
	$(CC) -shared -o lib/libtree.so tree.o
	ar rcs lib/libtree-static.a tree.o

arr:
	$(CC) -o bin/test_tree_arr test_tree_arr.c -Llib -ltree-static

char:
	$(CC) -o bin/test_tree_char test_tree_char.c -Llib -ltree-static

class:
	$(CPP) -o bin/test_tree_class test_tree_class.cpp -Llib -ltree-static

int:
	$(CC) -o bin/test_tree_int test_tree_int.c -Llib -ltree-static

struct:
	$(CC) -o bin/test_tree_struct test_tree_struct.c -Llib -ltree-static

clean:
	rm tree.o
	rm -rf lib
	rm -rf bin
