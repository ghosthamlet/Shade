def parser():
    os.system("bison -d parser/shade.y")
    os.system("flex -d parser/shade.l")
    os.system("gcc -c shade.tab.c -o parser.o -Iinclude")
    os.system("gcc -c s
