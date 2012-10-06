%include "shade.asm"
shextern
shdata
integer test1,1
integer test2,2
integer test3,3
defbss
defmain
shinit
shsetint _a0,test1
shsetint _a1,test2
shsetint _a2,test3
shcall add,_a1,_a2
shmov _a1,uscore
shcall add,_a0,_a1
shmov _a0,uscore
exit
