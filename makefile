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

	#UNIT TESTS START HERE
	diff test_ans/1 tmp_ans/1
	diff test_ans/2 tmp_ans/2
	diff test_ans/3 tmp_ans/3
	diff test_ans/4 tmp_ans/4
	diff test_ans/5 tmp_ans/5
	diff test_ans/6 tmp_ans/6
	diff test_ans/7 tmp_ans/7
	diff test_ans/8 tmp_ans/8

clean:
	rm *.gcno *.gcda *.gcov ./a.out
	ls
