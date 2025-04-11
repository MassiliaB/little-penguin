obj-m += main.o
MODULE_DIR := /usr/src/linux
PWD := $(shell pwd)

default:
	make -C $(MODULE_DIR) M=$(PWD) modules

clean:
	make -C $(MODULE_DIR) M=$(PWD) clean

