%macro shextern 0
		extern libshadeinit
		extern setValueInt
		extern setValueString
		extern getValue
		extern getAttr
		extern setAttr
		extern callFreeFunction0Arg
		extern callFreeFunction1Arg
		extern callFreeFunction2Arg
		extern callFreeFunction3Arg
%endmacro

%macro shinit 0
		ccall libshadeinit
%endmacro

%macro shdata 0
		defdata
		string uscore,"_" ;The underscore is used as the default variable to store a result in.
		string puts,"puts"
%endmacro

%macro shbss 0
		defbss
%endmacro

%macro shcall 1
		ccall callFreeFunction0Arg,uscore,%1
%endmacro

%macro shcall 2
		ccall callFreeFunction1Arg,uscore,%1,%2
%endmacro

%macro shcall 3
		ccall callFreeFunction2Arg,uscore,%1,%2,%3
%endmacro

%macro shcall 4
		ccall callFreeFunction3Arg,uscore,%1,%2,%3,%4
%endmacro

%macro shsetint 2
		ccall setValueInt,%1,%2
%endmacro

%macro shsetstr 2
		ccall setValueString,%1,%2
%endmacro

%macro shmov 2
		ccall getValue,%1,%2
%endmacro

%macro exit 0
		mov		ebx,0	;first syscall argument: exit code
        mov     eax,1   ;system call number (sys_exit)
        int     0x80	;call kernel
%endmacro

%macro flushargs 0
		add		esp,byte 8      ; `byte' saves space
%endmacro

%macro defmain 0
		section .text
			global main
		main:
%endmacro

%macro defdata 0
		section .data
%endmacro

%macro defbss 0
		section .bss
%endmacro

%macro string 2
		%1: db %2,0x0
%endmacro

%macro stringnl 2
		%1: db %2,0xa,0x0
%endmacro

%macro integer 2
		%1: db %2
%endmacro

%macro ccall 1
		call    %1
%endmacro

%macro ccall 2
		push	%2
		call	%1
		flushargs
%endmacro

%macro ccall 3
		push	%3
		push	%2
		call	%1
		flushargs
%endmacro

%macro ccall 4
		push	%4
		push	%3
		push	%2
		call	%1
		flushargs
%endmacro

%macro ccall 5
		push	%5
		push	%4
		push	%3
		push	%2
		call	%1
		flushargs
%endmacro

%macro ccall 6
		push	%6
		push	%5
		push	%4
		push	%3
		push	%2
		call	%1
		flushargs
%endmacro
