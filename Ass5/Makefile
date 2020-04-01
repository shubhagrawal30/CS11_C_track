#
# CS 11: Makefile for C track, assignment 5.
#

CC     = gcc
CFLAGS = -g -Wall -Wstrict-prototypes -ansi -pedantic

all: ver_arr ver_po

ver_arr: ver_arr.o memcheck.o
	$(CC) ver_arr.o memcheck.o -o ver_arr

ver_po: ver_po.o memcheck.o
	$(CC) ver_po.o memcheck.o -o ver_po

ver_po.o: ver_po.c memcheck.h
	$(CC) $(CFLAGS) -c ver_po.c

memcheck.o: memcheck.c memcheck.h
	$(CC) $(CFLAGS) -c memcheck.c

ver_arr.o: ver_arr.c memcheck.h
	$(CC) $(CFLAGS) -c ver_arr.c

check:
	c_style_check ver_arr.c
	c_style_check ver_po.c

clean:
	rm -f *.o ver_arr ver_po memcheck



