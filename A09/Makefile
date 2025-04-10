obj-m += main.o
MODULE_DIR := /usr/src/linux-next 
PWD := $(shell pwd)

default:
	make -C $(MODULE_DIR) M=$(PWD) modules

clean:
	make -C $(MODULE_DIR) M=$(PWD) clean

