CC=g++
LD=g++
CCFLAGS=
CCFLAGS_DEBUG=$(CCFLAGS) -g
CCFLAGS_DIST=$(CCFLAGS) -O2 -march=athlon-xp
#-xtarget=native -xunroll=512 -xipo -xvector=simd -xarch=sse2 -O5
LDFLAGS=
SRCDIR=.
DISTDIR=./dist
PKGDIR=./packages
PROG=id3grep
SOURCEEDITOR=/opt/SUNWspro/bin/xemacs


all: test

dist: dbuild
	cp id3grep.cc id3read.cc directory.cc id3grep.h id3read.h directory.h $(DISTDIR)
	@((cd $(DISTDIR) && tar cf $(PROG).tar id3grep.cc id3read.cc directory.cc id3grep.h id3read.h directory.h Makefile copyright.txt copyright.html && bzip2 $(PROG).tar && mv $(PROG).tar.bz2 $(PKGDIR) && echo 'package built.' ) &)
	@echo "packaging asynchronous."

test: debug

debug: tbuild
	#gdb --exec=./id3grep
	#(cd testmp3s && ls -1|../id3grep -p -x A)
	./id3grep -d ./testmp3s -v -p Ang 

tbuild: tcompile
	$(CC) $(LDFLAGS) -o id3grep id3grep.o id3read.o directory.o

tcompile:
	$(CC) $(CCFLAGS_DEBUG) -c id3grep.cc
	$(CC) $(CCFLAGS_DEBUG) -c id3read.cc
	$(CC) $(CCFLAGS_DEBUG) -c directory.cc

# maybe add targets and deps

dbuild: dcompile
	$(CC) $(LDFLAGS) -o id3grep id3grep.o id3read.o directory.o

dcompile:
	$(CC) $(CCFLAGS_DIST) -c id3grep.cc
	$(CC) $(CCFLAGS_DIST) -c id3read.cc
	$(CC) $(CCFLAGS_DIST) -c directory.cc

# maybe add targets and deps

clean:
	rm -R -f *.o
	rm -f $(PROG)

edit:
	$(SOURCEEDITOR) *.h *.cc &
	$(SOURCEEDITOR) Makefile &
