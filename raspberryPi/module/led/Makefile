CC = gcc
obj-m := led_module.o
KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
	@echo "Compiling for kernel version: $(shell uname -r)"

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
