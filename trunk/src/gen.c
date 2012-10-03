#include "gen.h"
FILE *OUTPUT;
void generate_line(char *line) {
    fprintf("%s\n", line);
}
void start_generation() {
    OUTPUT = fopen("a.out.asm", "w");
    generate_line("shextern\ndefdata\ndefbss\ndefmain\nshinit");
}
void push_int(int i) {
    generate_line(
}
void push_const_int(int i) {
}
