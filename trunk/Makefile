CFILES = src/codegen.c src/node.c src/treewalker.c src/gen.c src/type.c
CFLAGS = "-Iinclude"
INSTALL = install
INSTALL_PROGRAM = $(INSTALL)
INSTALL_DATA = $(INSTALL) -m 644
prefix = /usr/local
exec_prefix = $(prefix)
bindir = $(prefix)/bin
datarootdir = $(prefix)/share
datadir = $(datarootdir)
libdir = $(exec_prefix)/lib
all : parser objects
	gcc codegen.o node.o treewalker.o gen.o type.o parser.o lexer.o -g -Wall -o shade
objects : $(CFILES)
	gcc $(CFILES) -c -g -Wall -Iinclude
lib: libshade.cpp
	g++ libshade.cpp -o libshade.so -c -g -fPIC -shared
parser: parser/shade.y parser/shade.l
	bison -d -t parser/shade.y
	flex -d parser/shade.l
	gcc -c shade.tab.c -o parser.o -Iinclude -g
	gcc -c lex.yy.c -o lexer.o -Iinclude -g
install:
	$(INSTALL_PROGRAM) shade $(DESTDIR)$(bindir)/shade
	mkdir -p $(DESTDIR)$(datadir)/shade
	$(INSTALL_DATA) shade.asm $(DESTDIR)$(datadir)/shade/shade.asm
	$(INSTALL_DATA) libshade.so $(DESTDIR)$(libdir)/libshade.so
uninstall:
	rm $(DESTDIR)$(bindir)/shade
	rm $(DESTDIR)$(datadir)/shade/shade.asm
	rm $(DESTDIR)$(libdir)/libshade.so
clean:
	rm src/*.o
	rm shade.tab.c lex.yy.c
	rm *.o
