CFLAGS = -g -Wall -Werror -O3
GCC = gcc $(CFLAGS) 
OBJS = sorting_main.o sorting.o 
VAL = valgrind --tool=memcheck --leak-check=full --show-reachable=yes

sorting_main:$(OBJS)
		$(GCC) $(OBJS) -o proj1

sorting_main.o: sorting_main.c sorting.h
	$(GCC) -c sorting_main.c

sorting.o:sorting.c sorting.h
	$(GCC) -c sorting.c

test: sorting_main
	#./proj1 sample-input.txt test1.txt
 
	diff sample-output.txt bubtest.txt
	diff sample-output.txt shelltest.txt


 memory: sorting_main
	$(VAL) proj1

clean:
	rm -f *.o
	rm -f  proj1
	rm -f core.*
	rm -f bsampletest.txt bssampletest.txt  ssampletest.txt sssample.txt ssample.txt
	rm -f test1.txt text1.txt test2.txt test3.txt 
	rm -f *.gcda *.gcno *.gcov gmon.out