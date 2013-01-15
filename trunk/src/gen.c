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
int BASE_OFFSET = 0;
void write_output(char *o)
{
	fprintf(OUTPUT, "%s\n", o);
}
void set_func_context(int c)
{
	FUNC_CONTEXT = c;
	BASE_OFFSET = 0;
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
	generate_line("push ebp");
	generate_line("mov ebp,esp");
	generate_line("sub esp,100");
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
void compare(char *setname)
{
	char sprintf_fodder[100];
	generate_line("pop eax");
	generate_line("pop ebx");
	generate_line("cmp eax,ebx");
	sprintf(sprintf_fodder, "%s al", setname);
	generate_line(sprintf_fodder);
	generate_line("movsx eax,al");
	generate_line("push eax");
}
void call_function(char *name)
{
	char sprintf_fodder[100];
	debug("CALL_FUNCTION: %s", get_symbol_location(name));
	sprintf(sprintf_fodder, "mov eax,[%s]", get_symbol_location(name));
	generate_line(sprintf_fodder);
	generate_line("call eax");
	generate_line("push eax");
}
void assign_scalar(char *name)
{
	char sprintf_fodder[100];
	generate_line("pop eax");
	sprintf(sprintf_fodder, "mov dword [%s],eax", get_symbol_location(name));
	generate_line(sprintf_fodder);
	generate_line("push eax");
}
void assign_vector(char *name)
{
	char sprintf_fodder[100];
	generate_line("pop eax");
	generate_line("pop ebx");
	sprintf(sprintf_fodder, "mov [%s+ebx*%d], eax", get_symbol_location(name), 4);
	generate_line(sprintf_fodder);
	generate_line("push eax");
}
void get_scalar(char *name)
{
	debug("get_scalar");
	char sprintf_fodder[100];
	symtab_entry *symdata = get_symbol_data(name);
	sprintf(sprintf_fodder, "push dword [%s]", symdata->location);
	generate_line(sprintf_fodder);
}
void get_vector(char *name)
{
	debug("get_vector");
	char sprintf_fodder[100];
	generate_line("pop eax");
	symtab_entry *symdata = get_symbol_data(name);
	sprintf(sprintf_fodder, "push dword [%s+eax*%d]", symdata->location, symdata->type->abase->size);
	generate_line(sprintf_fodder);
}
void declare_scalar(char *name, type_decl *type)
{
	char sprintf_fodder[100];
	//if (FUNC_CONTEXT) {
		BASE_OFFSET += type->size;
		sprintf(sprintf_fodder, "ebp-%d", BASE_OFFSET);
	//} else {
	//	sprintf(sprintf_fodder, "%s: resb %d", name, type->size);
	//	generate_bss(sprintf_fodder);
	//	sprintf(sprintf_fodder, "%s", name);
	//}
	new_symbol(name, sprintf_fodder, type);
}
void declare_vector(char *name, type_decl *type)
{
	char sprintf_fodder[100];
	//if (FUNC_CONTEXT) {
		BASE_OFFSET += type->size;
		sprintf(sprintf_fodder, "ebp-%d", BASE_OFFSET);
	//} else {
	//	sprintf(sprintf_fodder, "%s: resb %d", name, type->size);
	//	generate_bss(sprintf_fodder);
	//	sprintf(sprintf_fodder, "%s", name);
	//}
	new_symbol(name, sprintf_fodder, type);
}
