 CONFIG_MODULE_SIG=n
obj-m :=showfamily.o
showfamily-objs:=family.o
KDIR:=/lib/modules/$(shell uname -r)/build
PWD:=$(shell pwd)
default:
        make -C $(KDIR) M=$(PWD) modules
clean:
        make -C $(KDIR) M=$(PWD) clean
