#include "gen.h"
FILE *OUTPUT;
FILE *DATA;
char data[1024*1024];
FILE *CODE;
char code[1024*1024];
int ARG_N = 0;
int CONST_N = 0;
void write_output(char *o) {
	fprintf(OUTPUT, "%s\n", o);
}
void generate_line(char *line) {
	fprintf(CODE, "%s\n", line);
}
void generate_data(char *line) {
	fprintf(DATA, "%s\n", line);
}
void start_generation() {
	DATA = fmemopen(data, 1024*1024, "w");
	CODE = fmemopen(code, 1024*1024, "w");
}
void stop_generation() {
	OUTPUT = fopen("a.out.asm", "w");
	write_output("%include \"shade.asm\"\nshextern\nshdata");
	fclose(DATA);
	write_output(data);
	write_output("defbss\ndefmain\nshinit");
	fclose(CODE);
	write_output(code);
	write_output("exit");
	fclose(OUTPUT);
}
void push_int(int i) {
	char sprintf_fodder[100];
	sprintf(sprintf_fodder, "shsetint _a%d,_const%d", get_argn(), CONST_N);
	inc_argn();
	generate_line(sprintf_fodder);
	sprintf(sprintf_fodder, "integer _const%d,%d", CONST_N, i);
	generate_data(sprintf_fodder);
	++CONST_N;
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
