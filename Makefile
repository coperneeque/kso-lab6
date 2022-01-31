# Makefile

CFLAGS = -Wall -c
LDFLAGS =

all: main.o filesys.o test1.o
	cc $(LDFLAGS) main.o filesys.o -o main
	cc $(LDFLAGS) test1.o filesys.o -o test1

main.o: main.c filesys.h
	cc $(CFLAGS) main.c

filesys.o: filesys.c filesys.h
	cc $(CFLAGS) filesys.c

test1.o: test1.c filesys.h
	cc $(CFLAGS) test1.c

# clean:
#     rm -f *.o main
