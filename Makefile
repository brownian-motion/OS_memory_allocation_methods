all: proj2 test

proj2: src/*.c src/*.h
	gcc -o $@ $^

test:
	./proj2 1024