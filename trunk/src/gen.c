#include "gen.h"
FILE *OUTPUT;
FILE *DATA;
char __data[1024*1024];
FILE *BSS;
char __bss[1024*1024];
FILE *CODE;
char __code[1024*1024];
FILE *EXTERNS;
char __externs[1024*1024];
FILE *FUNCS;
char __funcs[1024*1024];
int STRCOUNT = 0;
int FUNC_CONTEXT = 0;
void write_output(char *o)
{
	fprintf(OUTPUT, "%s\n", o);
}
void set_func_context(int c)
{
	FUNC_CONTEXT = c;
}
void generate_line(char *line)
{
	if (FUNC_CONTEXT) {
		generate_func(line);
	} else {
		generate_code(line);
	}
}
void generate_code(char *line)
{
	fprintf(CODE, "%s\n", line);
}
void generate_data(char *line)
{
	fprintf(DATA, "%s\n", line);
}
void generate_bss(char *line)
{
	fprintf(BSS, "%s\n", line);
}
void generate_extern(char *line)
{
	fprintf(EXTERNS, "%s\n", line);
}
void generate_func(char *line)
{
	fprintf(FUNCS, "%s\n", line);
}
void start_generation()
{
	DATA = fmemopen(__data, 1024*1024, "w");
	BSS = fmemopen(__bss, 1024*1024, "w");
	CODE = fmemopen(__code, 1024*1024, "w");
	EXTERNS = fmemopen(__externs, 1024*1024, "w");
	FUNCS = fmemopen(__funcs, 1024*1024, "w");
	generate_data("section .data");
	generate_bss("section .bss");
	generate_func("section .text");
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
	fclose(BSS);
	write_output(__bss);
	fclose(FUNCS);
	write_output(__funcs);
	fclose(CODE);
	write_output(__code);
	write_output("mov ebx,0\nmov eax,1\nint 0x80");
	fclose(OUTPUT);
}
void push_int(int i)
{
	char sprintf_fodder[100];
	sprintf(sprintf_fodder, "push %d", i);
	generate_line(sprintf_fodder);
}
void push_string(char *s)
{
	char sprintf_fodder[100];
	sprintf(sprintf_fodder, "__str%d: db %s,10,0", STRCOUNT, s);
	generate_data(sprintf_fodder);
	sprintf(sprintf_fodder, "push __str%d", STRCOUNT);
	generate_line(sprintf_fodder);
	STRCOUNT++;
}
