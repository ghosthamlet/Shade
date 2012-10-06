#include "gen.h"
FILE *OUTPUT;
int ARG_N = 0;
void generate_line(char *line) {
    fprintf(OUTPUT, "%s\n", line);
}
void start_generation() {
    OUTPUT = fopen("a.out.asm", "w");
    generate_line("%include \"shade.asm\"\nshextern\nshdata\ndefbss\ndefmain\nshinit");
}
void stop_generation() {
    generate_line("exit");
    fclose(OUTPUT);
}
void push_int(int i) {
    char sprintf_fodder[100];
    sprintf(sprintf_fodder, "shsetint _a%d,%d", get_argn(), i);
    inc_argn();
    generate_line(sprintf_fodder);
}
void push_name(const char *n) {
    char sprintf_fodder[100];
    sprintf(sprintf_fodder, "shmov _a%d,%s", get_argn(), n);
    inc_argn();
    generate_line(sprintf_fodder);
}
int get_argn() {return ARG_N;}
void set_argn(int i) {ARG_N=i;}
void inc_argn() {++ARG_N;}
void dec_argn() {--ARG_N;}
