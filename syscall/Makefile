EXAMPLES := hello syscall exocall

CFLAGS = -g -static
LDFLAGS = -g -static

all : $(EXAMPLES)

main.o : CFLAGS += -O3

all : main
main : main.o init.o

clean :
	rm -f *.o main $(EXAMPLES)
