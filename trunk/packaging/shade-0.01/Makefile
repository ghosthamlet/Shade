OBJECTS = parser.o lexer.o src/codegen.o src/node.o src/treewalker.o src/gen.o src/type.o src/utils.o src/symtab.o
CFLAGS = -I. -Iinclude -Wall -g
YFLAGS = -d
LFLAGS = 
INSTALL = install
INSTALL_PROGRAM = $(INSTALL)
INSTALL_DATA = $(INSTALL) -m 644
VERSION = 0.01
prefix = /usr/local
exec_prefix = $(prefix)
bindir = $(prefix)/bin
datarootdir = $(prefix)/share
datadir = $(datarootdir)
libdir = $(exec_prefix)/lib
all : $(OBJECTS)
	gcc $(OBJECTS) -g -Wall -o shade
parser.o: parser/shade.y
	bison -d -t parser/shade.y
	gcc -c shade.tab.c -o parser.o -Iinclude -g
lexer.o: parser.o parser/shade.l
	flex -d parser/shade.l
	gcc -c lex.yy.c -o lexer.o -Iinclude -g
tarball:
	rm packaging/shade-* -r
	mkdir packaging/shade-$(VERSION)
	cp -r Makefile parser src include packaging/shade-$(VERSION)
	tar -czf shade-$(VERSION).tar.gz packaging/shade-$(VERSION)
install:
	$(INSTALL_PROGRAM) shade $(DESTDIR)$(bindir)/shade
uninstall:
	rm $(DESTDIR)$(bindir)/shade
clean:
	rm shade.tab.c shade.tab.h lex.yy.c
	rm $(OBJECTS)
