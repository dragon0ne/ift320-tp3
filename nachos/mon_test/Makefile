# use normal make for this Makefile
#
# Makefile for building user programs to run on top of Nachos
#
# Several things to be aware of:
#
#    Nachos assumes that the location of the program startup routine (the
# 	location the kernel jumps to when the program initially starts up)
#       is at location 0.  This means: start.o must be the first .o passed 
# 	to ld, in order for the routine "Start" to be loaded at location 0
#

# if you are cross-compiling, you need to point to the right executables
# and change the flags to ld and the build procedure for as
#GCCDIR = /home/public/Projets/girard2/nachos/gnu/decstation-ultrix/bin/
GCCDIR = /opt/mips/decstation-ultrix/bin/
LDFLAGS = -T script -N
ASFLAGS = 
CPPFLAGS = $(INCDIR)


# if you aren't cross-compiling:
#GCCDIR = 
#LDFLAGS = -N -T 0
#ASFLAGS =
#CPPFLAGS = -P $(INCDIR)


CC = $(GCCDIR)gcc
AS = $(GCCDIR)as
LD = $(GCCDIR)ld

CPP = /usr/ccs/lib/cpp
INCDIR =-I../userprog -I../threads
CFLAGS = -G 0 -c $(INCDIR)

all: halt test1 test2 test2a test3 test3a boucle test_err1 test_err2 test_err3\
demarre_t2 demarre_t3 demarre_err demarre_thread

start.o: start.s 
	$(CPP) $(CPPFLAGS) start.s > strt.s
	$(AS) $(ASFLAGS) -o start.o strt.s
	rm strt.s

halt.o: halt.c
	$(CC) $(CFLAGS) -c halt.c
halt: halt.o start.o
	$(LD) $(LDFLAGS) start.o halt.o -o halt.coff
	./coff2noff halt.coff halt

test1.o: test1.c
	$(CC) $(CFLAGS) -c test1.c
test1: test1.o start.o
	$(LD) $(LDFLAGS) start.o test1.o -o test1.coff
	./coff2noff test1.coff test1

demarre_t2.o: demarre_t2.c
	$(CC) $(CFLAGS) -c demarre_t2.c
demarre_t2: demarre_t2.o demarre_t2.o
	$(LD) $(LDFLAGS) start.o demarre_t2.o -o demarre_t2.coff
	./coff2noff demarre_t2.coff demarre_t2
	
demarre_t3.o: demarre_t3.c
	$(CC) $(CFLAGS) -c demarre_t3.c
demarre_t3: demarre_t3.o start.o
	$(LD) $(LDFLAGS) start.o demarre_t3.o -o demarre_t3.coff
	./coff2noff demarre_t3.coff demarre_t3

demarre_err.o: demarre_err.c
	$(CC) $(CFLAGS) -c demarre_err.c
demarre_err: demarre_err.o start.o
	$(LD) $(LDFLAGS) start.o demarre_err.o -o demarre_err.coff
	./coff2noff demarre_err.coff demarre_err


test2.o: test2.c
	$(CC) $(CFLAGS) -c test2.c
test2: test2.o start.o
	$(LD) $(LDFLAGS) start.o test2.o -o test2.coff
	./coff2noff test2.coff test2

test2a.o: test2a.c
	$(CC) $(CFLAGS) -c test2a.c
test2a: test2a.o start.o
	$(LD) $(LDFLAGS) start.o test2a.o -o test2a.coff
	./coff2noff test2a.coff test2a

test3.o: test3.c
	$(CC) $(CFLAGS) -c test3.c
test3: test3.o start.o
	$(LD) $(LDFLAGS) start.o test3.o -o test3.coff
	./coff2noff test3.coff test3

boucle.o: boucle.c
	$(CC) $(CFLAGS) -c boucle.c
boucle: boucle.o start.o
	$(LD) $(LDFLAGS) start.o boucle.o -o boucle.coff
	./coff2noff boucle.coff boucle


test3a.o: test3a.c
	$(CC) $(CFLAGS) -c test3a.c
test3a: test3a.o start.o
	$(LD) $(LDFLAGS) start.o test3a.o -o test3a.coff
	./coff2noff test3a.coff test3a

test_err1.o: test_err1.c
	$(CC) $(CFLAGS) -c test_err1.c
test_err1: test_err1.o start.o
	$(LD) $(LDFLAGS) start.o test_err1.o -o test_err1.coff
	./coff2noff test_err1.coff test_err1

test_err2.o: test_err2.c
	$(CC) $(CFLAGS) -c test_err2.c
test_err2: test_err2.o start.o
	$(LD) $(LDFLAGS) start.o test_err2.o -o test_err2.coff
	./coff2noff test_err2.coff test_err2

test_err3.o: test_err3.c
	$(CC) $(CFLAGS) -c test_err3.c
test_err3: test_err3.o start.o
	$(LD) $(LDFLAGS) start.o test_err3.o -o test_err3.coff
	./coff2noff test_err3.coff test_err3


demarre_thread.o: demarre_thread.c
	$(CC) $(CFLAGS) -c demarre_thread.c
demarre_thread: demarre_thread.o start.o
	$(LD) $(LDFLAGS) start.o demarre_thread.o -o demarre_thread.coff
	./coff2noff demarre_thread.coff demarre_thread

