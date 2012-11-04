#include "gen.h"
FILE *OUTPUT;
FILE *DATA;
char __data[1024*1024];
FILE *CODE;
char __code[1024*1024];
FILE *EXTERNS;
char __externs[1024*1024];
int ARG_N = 0;
int CONST_N = 0;
void write_output(char *o)
{
	fprintf(OUTPUT, "%s\n", o);
}
void generate_line(char *line)
{
	fprintf(CODE, "%s\n", line);
}
void generate_data(char *line)
{
	fprintf(DATA, "%s\n", line);
}
void generate_extern(char *line)
{
	fprintf(EXTERNS, "%s\n", line);
}
void start_generation()
{
	DATA = fmemopen(__data, 1024*1024, "w");
	CODE = fmemopen(__code, 1024*1024, "w");
	EXTERNS = fmemopen(__externs, 1024*1024, "w");
	generate_data("section .data");
	generate_line("section .text");
	generate_line("global main");
	generate_line("main:");
}
void stop_generation()
{
	OUTPUT = fopen("a.out.asm", "w");
	fclose(EXTERNS);
	write_output(__externs);
	fclose(DATA);
	write_output(__data);
	fclose(CODE);
	write_output(__code);
	write_output("mov ebx,0\nmov eax,1\nint 0x80");
	fclose(OUTPUT);
}
void push_int(int i)
{
	//char sprintf_fodder[100];
	//sprintf(sprintf_fodder, "shsetint _a%d,_const%d", get_argn(), CONST_N);
	//inc_argn();
	//generate_line(sprintf_fodder);
	//sprintf(sprintf_fodder, "integer _const%d,%d", CONST_N, i);
	//generate_data(sprintf_fodder);
	//++CONST_N;
	char sprintf_fodder[100];
	sprintf(sprintf_fodder, "mov eax,%d", i);
	generate_line(sprintf_fodder);
	generate_line("push eax");
}
void push_name(const char *n)
{
	char sprintf_fodder[100];
	sprintf(sprintf_fodder, "shmov _a%d,%s", get_argn(), n);
	inc_argn();
	generate_line(sprintf_fodder);
}
int get_argn()
{
	return ARG_N;
}
void set_argn(int i)
{
	ARG_N=i;
}
void inc_argn()
{
	++ARG_N;
}
void dec_argn()
{
	--ARG_N;
}
