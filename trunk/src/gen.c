#include "gen.h"
FILE *OUTPUT;
void generate_line(char *line) {
    fprintf(OUTPUT, "%s\n", line);
}
void start_generation() {
    OUTPUT = fopen("a.out.asm", "w");
    generate_line("shextern\ndefdata\ndefbss\ndefmain\nshinit");
}
void push_int(int i) {
    char sprintf_fodder[100];
    sprintf(sprintf_fodder, "shpush %d", i);
    generate_line(sprintf_fodder);
}
void push_name(const char *n) {
    char sprintf_fodder[100];
    sprintf(sprintf_fodder, "shpush %s", n);
    generate_line(sprintf_fodder);
}
