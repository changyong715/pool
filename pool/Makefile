.PHONY : clean all

all :  main

main : main.o threadpool.o condition.o
	gcc $^ -o $@ -lpthread

%.o : %.c
	gcc -c $< -o $@

clean:
	rm -rf *.o main

