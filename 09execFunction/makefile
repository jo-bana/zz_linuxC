all:exec numAndChar

exec:exec.o
	gcc $^ -o $@

numAndChar:numAndChar.o
	gcc $^ -o $@

.PHONY:clean
clean:
	rm -rf *.o exec numAndChar 
