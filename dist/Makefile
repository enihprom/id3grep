
#CC=/opt/SUNWspro/bin/CC
CC=g++

LD=ld
CCFLAGS=
CCFLAGS_DEBUG=$(CCFLAGS) -g

#CCFLAGS_DIST=$(CCFLAGS) -xtarget=native -xunroll=512 -xipo -xvector=simd -xarch=sse2 -O5
CCFLAGS_DIST=-O2

LDFLAGS=-lgen
SRCDIR=.
DISTDIR=./packages

all: dbuild

dist: dbuild
	cd $(SRCDIR)
	tar cf $(DISTDIR)/id3grep.tar id3grep id3grep.cc id3read.cc directory.cc id3grep.h id3read.h directory.h Makefile copyright.txt copyright.html
	bzip2 $(DISTDIR)/id3grep.tar

dbuild: dcompile
	$(CC) $(LDFLAGS) -o id3grep id3grep.o id3read.o directory.o

dcompile:
	$(CC) $(CCFLAGS_DIST) -c id3grep.cc
	$(CC) $(CCFLAGS_DIST) -c id3read.cc
	$(CC) $(CCFLAGS_DIST) -c directory.cc

# maybe add targets and deps

clean:
	rm -R -f *.o

