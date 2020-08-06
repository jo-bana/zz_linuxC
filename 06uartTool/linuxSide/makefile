CC = gcc

interface:interface.o uart.o 
	$(CC) $^ -o $@

.PHONY:clean
clean:
	rm -rf interface *.o
