CC = gcc
EXEC = sht20_native
OBJS = $(EXEC).o

$(EXEC) : $(OBJS)
	$(CC) -o $@ $^ 

clean:
	rm -f *.o
	rm -f *.i
	rm -f *.s
	rm -f $(EXEC)
