OBJECTS = src/codegen.o src/node.o src/treewalker.o
CFLAGS = "-Iinclude"
all : parser $(OBJECTS)
	gcc $(OBJECTS) parser.o lexer.o -g -Wall -o shade
lib: libshade/libshade.cpp
	g++ libshade/libshade.cpp -o libshade.o -c
parser: parser/shade.y parser/shade.l
	bison -d parser/shade.y
	flex -d parser/shade.l
	gcc -c shade.tab.c -o parser.o -Iinclude
	gcc -c lex.yy.c -o lexer.o -Iinclude
clean :
	rm src/*.o
	rm shade.tab.c lex.yy.c
	rm *.o
