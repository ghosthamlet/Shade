OBJECTS = src/codegen.o src/node.o src/treewalker.o src/gen.o
CFLAGS = "-Iinclude"
all : parser $(OBJECTS)
	gcc $(OBJECTS) parser.o lexer.o -g -Wall -o shade
lib: libshade.cpp
	g++ libshade.cpp -o libshade.so -c -g -fPIC -shared
parser: parser/shade.y parser/shade.l
	bison -d parser/shade.y
	flex -d parser/shade.l
	gcc -c shade.tab.c -o parser.o -Iinclude -g
	gcc -c lex.yy.c -o lexer.o -Iinclude -g
clean :
	rm src/*.o
	rm shade.tab.c lex.yy.c
	rm *.o
