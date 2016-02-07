# Copyright (C) 1994, 1995-8, 1999 Free Software Foundation, Inc.
# This Makefile.in is free software; the Free Software Foundation
# gives unlimited permission to copy and/or distribute it,
# with or without modifications, as long as this notice is preserved.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY, to the extent permitted by law; without
# even the implied warranty of MERCHANTABILITY or FITNESS FOR A
# PARTICULAR PURPOSE.

CC=gcc
VERSION=0.0.1
CFLAGS=-g -O2
INCLUDES=config.h standalone.h child.h version.h
SOURCES=main.c config.c standalone.c child.c 
OBJS=main.o config.o standalone.o child.o
PACKAGE=g-pop3d
FILES=$(SOURCES) $(INCLUDES)

gpop: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(PACKAGE)

.c.o: $(INCLUDES)
	$(CC) -c $(CFLAGS) $<

clean:
	rm -f g-pop3d g-pop3d.core core *.o

	