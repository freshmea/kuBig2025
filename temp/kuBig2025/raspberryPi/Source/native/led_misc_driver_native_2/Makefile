CC = gcc
EXEC = led_misc_driver_native_2
OBJS = $(EXEC).o

$(EXEC) : $(OBJS)
	$(CC) -o $@ $^ 

clean:
	rm -f *.o
	rm -f *.i
	rm -f *.s
	rm -f $(EXEC)
