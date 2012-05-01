%include "shade.asm"
shextern
shdata
string msg,"Yo!"
string __index_msg,"msg"
shbss
defmain
shinit
shsetstr __index_msg,msg
shcall puts,__index_msg
exit
