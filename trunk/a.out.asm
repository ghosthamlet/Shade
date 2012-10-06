%include "shade.asm"
shextern
shdata
integer _const0,1
integer _const1,1

defbss
defmain
shinit
shsetint _a0,_const0
shsetint _a1,_const1
shcall add,_a0,_a1
shmov _a0,uscore

exit
