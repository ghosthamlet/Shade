OBJECTS = parser.o lexer.o src/codegen.o src/node.o src/treewalker.o src/gen.o src/type.o src/utils.o src/symtab.o
CFLAGS = -I. -Iinclude -Wall -g
YFLAGS = -d
LFLAGS = 
INSTALL = install
INSTALL_PROGRAM = $(INSTALL)
INSTALL_DATA = $(INSTALL) -m 644
prefix = /usr/local
exec_prefix = $(prefix)
bindir = $(prefix)/bin
datarootdir = $(prefix)/share
datadir = $(datarootdir)
libdir = $(exec_prefix)/lib
all : parser $(OBJECTS)
	gcc $(OBJECTS) -g -Wall -o shade
parser: parser/shade.y parser/shade.l
	bison -d -t parser/shade.y
	flex -d parser/shade.l
	gcc -c shade.tab.c -o parser.o -Iinclude -g
	gcc -c lex.yy.c -o lexer.o -Iinclude -g
install:
	$(INSTALL_PROGRAM) shade $(DESTDIR)$(bindir)/shade
uninstall:
	rm $(DESTDIR)$(bindir)/shade
clean:
	rm shade.tab.c shade.tab.h lex.yy.c
	rm *.o
	rm src/*.o
