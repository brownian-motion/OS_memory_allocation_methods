all: proj2 tests

proj2: src/*.c src/*.h
	gcc -o $@ $^

clean:
	rm -f proj2 test*.in

tests: test1 test2 test3 test4 test5

test:
	mkdir $@

test%: test/%.in proj2 | test
	./proj2 BESTFIT 1024 $< 1>&2
	./proj2 FIRSTFIT 1024 $< 1>&2	