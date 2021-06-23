obj-m := trace_module.o
CFLAGS_trace_module.o := -I$(src) 
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm *~
