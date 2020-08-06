obj=div.o add.o sub.o mul.o	

libfour.a:$(obj)
	ar -rc libfour.a $(obj)	
div.o:div.c
	gcc -c div.c
add.o:add.c
	gcc -c add.c
sub.o:sub.c
	gcc -c sub.c
mul.o:mul.c
	gcc -c mul.c

.PHONY:clean
clean:
	rm -rf *.o
