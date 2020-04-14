exe: $(patsubst %.c,%.o,$(wildcard *.c))
	gcc --coverage $^ -o $@
	valgrind ./exe

%.o: %.c
	gcc -c -MD $<

include $(wildcard *.d)

.PHONY: clean makegcov

makegcov:
	gcc --coverage -O0 rand_mem.c avl.c unit.c
	valgrind ./a.out
	gcov unit.c -m 
	gcov avl.c -m 
	gcov rand_mem.c -m 

clean:
	rm *.gcno *.gcda *.gcov ./a.out
	ls
