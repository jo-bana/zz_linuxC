CC=gcc
all:client server
client:client.o 
	$(CC) $^ -o $@ -lpthread
server:server.o 
	$(CC) $^ -o $@ -lpthread

.PHONY:clean
clean:
	rm -rf server client *.o