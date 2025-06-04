CC = gcc

CFLAGS = -c -Wall

ifeq ($(BUILD), debug)   
CFLAGS += -O0 -g
else
CFLAGS += -O2 -s -DNDEBUG
endif

HEADER = -I./  
LIBRA = -lwiringPi  

all: ssd1306_test

ssd1306_test: ssd1306_test.o ssd1306_i2c.o
		$(CC) ssd1306_test.o ssd1306_i2c.o $(LIBRA) -o ssd1306_test

ssd1306_test.o: ssd1306_test.c
		$(CC) $(CFLAGS) $(HEADER) ssd1306_test.c

ssd1306_i2c.o: ssd1306_i2c.c
		$(CC) $(CFLAGS) $(HEADER) ssd1306_i2c.c

clean:
		rm *.o
		rm ssd1306_test
