exe: $(patsubst %.c,%.o,$(wildcard *.c))
	gcc --coverage $^ -o $@
	valgrind ./exe

%.o: %.c
	gcc -c -MD $<

include $(wildcard *.d)

.PHONY: clean makegcov

makegcov:
	gcc -Wall -Wextra --coverage -O0 avl.c unit.c rand_mem.c
	valgrind ./a.out
	gcov unit.c -m 
	gcov avl.c -m 
	gcov rand_mem.c -m 

clean:
	rm *.gcno *.gcda *.gcov exe ./a.out *.o *.d
	ls
