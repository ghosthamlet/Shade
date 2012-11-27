let SessionLoad = 1
if &cp | set nocp | endif
let s:so_save = &so | let s:siso_save = &siso | set so=0 siso=0
let v:this_session=expand("<sfile>:p")
silent only
cd ~/projects/Shade/trunk/parser
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
set shortmess=aoO
badd +1 ~/projects/Shade/trunk/Makefile
badd +22 ~/projects/Shade/trunk/parser/shade.l
badd +1 ~/projects/Shade/trunk/parser/shade.y
badd +1 ~/projects/Shade/trunk/src/codegen.c
badd +1 ~/projects/Shade/trunk/src/gen.c
badd +1 ~/projects/Shade/trunk/include/gen.h
badd +24 ~/projects/Shade/trunk/src/node.c
badd +1 ~/projects/Shade/trunk/include/node.h
badd +1 ~/projects/Shade/trunk/src/treewalker.c
badd +1 ~/projects/Shade/trunk/include/treewalker.h
badd +1 ~/projects/Shade/trunk/libshade/libshade.cpp
badd +1 ~/projects/Shade/trunk/libshade/shade.asm
badd +1 ~/projects/Shade/trunk/..
badd +1 ~/projects/Shade/trunk/shade.asm
badd +31 ~/projects/Shade/trunk/libshade.cpp
badd +7 ~/projects/Shade/trunk/src/type.c
badd +1 ~/projects/Shade/trunk/include/type.h
badd +1 ~/projects/Shade/trunk/include/debug.h
badd +1 ~/projects/Shade/trunk/include/symtab.h
badd +1 ~/projects/Shade/trunk/include/hash.h
badd +1 ~/projects/Shade/trunk/src/symtab.c
badd +7 ~/projects/Shade/trunk/include/utils.h
badd +1 ~/projects/Purge/trunk/include/utils.h
badd +1 ~/projects/Shade/trunk/src/utils.c
badd +0 ~/projects/Purge/trunk/src/utils.c
silent! argdel *
edit ~/projects/Shade/trunk/Makefile
set splitbelow splitright
set nosplitbelow
set nosplitright
wincmd t
set winheight=1 winwidth=1
argglobal
let s:l = 1 - ((0 * winheight(0) + 20) / 41)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
1
normal! 0100l
tabedit ~/projects/Shade/trunk/parser/shade.y
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
set nosplitbelow
set nosplitright
wincmd t
set winheight=1 winwidth=1
exe 'vert 1resize ' . ((&columns * 84 + 84) / 169)
exe 'vert 2resize ' . ((&columns * 84 + 84) / 169)
argglobal
let s:l = 87 - ((23 * winheight(0) + 20) / 41)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
87
let s:c = 71 - ((31 * winwidth(0) + 42) / 84)
if s:c > 0
  exe 'normal! 0' . s:c . 'lzs' . (71 - s:c) . 'l'
else
  normal! 071l
endif
wincmd w
argglobal
edit ~/projects/Shade/trunk/parser/shade.l
let s:l = 31 - ((30 * winheight(0) + 20) / 41)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
31
normal! 04l
wincmd w
exe 'vert 1resize ' . ((&columns * 84 + 84) / 169)
exe 'vert 2resize ' . ((&columns * 84 + 84) / 169)
tabedit ~/projects/Shade/trunk/src/codegen.c
set splitbelow splitright
set nosplitbelow
set nosplitright
wincmd t
set winheight=1 winwidth=1
argglobal
let s:l = 10 - ((9 * winheight(0) + 20) / 41)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
10
normal! 018l
lcd ~/projects/Shade/trunk/parser
tabedit ~/projects/Shade/trunk/include/gen.h
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
set nosplitbelow
set nosplitright
wincmd t
set winheight=1 winwidth=1
exe 'vert 1resize ' . ((&columns * 73 + 84) / 169)
exe 'vert 2resize ' . ((&columns * 95 + 84) / 169)
argglobal
let s:l = 8 - ((7 * winheight(0) + 20) / 41)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
8
normal! 017l
lcd ~/projects/Shade/trunk
wincmd w
argglobal
edit ~/projects/Shade/trunk/src/gen.c
let s:l = 14 - ((13 * winheight(0) + 20) / 41)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
14
normal! 02l
lcd ~/projects/Shade/trunk
wincmd w
exe 'vert 1resize ' . ((&columns * 73 + 84) / 169)
exe 'vert 2resize ' . ((&columns * 95 + 84) / 169)
tabedit ~/projects/Shade/trunk/include/node.h
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
set nosplitbelow
set nosplitright
wincmd t
set winheight=1 winwidth=1
exe 'vert 1resize ' . ((&columns * 87 + 84) / 169)
exe 'vert 2resize ' . ((&columns * 81 + 84) / 169)
argglobal
let s:l = 54 - ((40 * winheight(0) + 20) / 41)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
54
normal! 0
lcd ~/projects/Shade/trunk
wincmd w
argglobal
edit ~/projects/Shade/trunk/src/node.c
let s:l = 4 - ((3 * winheight(0) + 20) / 41)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
4
normal! 0
lcd ~/projects/Shade/trunk
wincmd w
exe 'vert 1resize ' . ((&columns * 87 + 84) / 169)
exe 'vert 2resize ' . ((&columns * 81 + 84) / 169)
tabedit ~/projects/Shade/trunk/include/treewalker.h
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
set nosplitbelow
set nosplitright
wincmd t
set winheight=1 winwidth=1
exe 'vert 1resize ' . ((&columns * 87 + 84) / 169)
exe 'vert 2resize ' . ((&columns * 81 + 84) / 169)
argglobal
let s:l = 4 - ((3 * winheight(0) + 20) / 41)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
4
normal! 0
lcd ~/projects/Shade/trunk
wincmd w
argglobal
edit ~/projects/Shade/trunk/src/treewalker.c
let s:l = 1 - ((0 * winheight(0) + 20) / 41)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
1
normal! 0
lcd ~/projects/Shade/trunk
wincmd w
exe 'vert 1resize ' . ((&columns * 87 + 84) / 169)
exe 'vert 2resize ' . ((&columns * 81 + 84) / 169)
tabedit ~/projects/Shade/trunk/include/symtab.h
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
set nosplitbelow
set nosplitright
wincmd t
set winheight=1 winwidth=1
exe 'vert 1resize ' . ((&columns * 84 + 84) / 169)
exe 'vert 2resize ' . ((&columns * 84 + 84) / 169)
argglobal
let s:l = 14 - ((13 * winheight(0) + 20) / 41)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
14
normal! 015l
lcd ~/projects/Shade/trunk
wincmd w
argglobal
edit ~/projects/Shade/trunk/src/symtab.c
let s:l = 3 - ((2 * winheight(0) + 20) / 41)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
3
normal! 0
lcd ~/projects/Shade/trunk
wincmd w
exe 'vert 1resize ' . ((&columns * 84 + 84) / 169)
exe 'vert 2resize ' . ((&columns * 84 + 84) / 169)
tabedit ~/projects/Shade/trunk/include/utils.h
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
set nosplitbelow
set nosplitright
wincmd t
set winheight=1 winwidth=1
exe 'vert 1resize ' . ((&columns * 84 + 84) / 169)
exe 'vert 2resize ' . ((&columns * 84 + 84) / 169)
argglobal
let s:l = 16 - ((15 * winheight(0) + 20) / 41)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
16
normal! 0
lcd ~/projects/Shade/trunk
wincmd w
argglobal
edit ~/projects/Shade/trunk/src/utils.c
let s:l = 18 - ((17 * winheight(0) + 20) / 41)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
18
normal! 01l
lcd ~/projects/Shade/trunk
wincmd w
exe 'vert 1resize ' . ((&columns * 84 + 84) / 169)
exe 'vert 2resize ' . ((&columns * 84 + 84) / 169)
tabedit ~/projects/Shade/trunk/include/type.h
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
set nosplitbelow
set nosplitright
wincmd t
set winheight=1 winwidth=1
exe 'vert 1resize ' . ((&columns * 84 + 84) / 169)
exe 'vert 2resize ' . ((&columns * 84 + 84) / 169)
argglobal
let s:l = 10 - ((9 * winheight(0) + 20) / 41)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
10
normal! 0
lcd ~/projects/Shade/trunk
wincmd w
argglobal
edit ~/projects/Shade/trunk/src/type.c
let s:l = 7 - ((6 * winheight(0) + 20) / 41)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
7
normal! 011l
lcd ~/projects/Shade/trunk
wincmd w
exe 'vert 1resize ' . ((&columns * 84 + 84) / 169)
exe 'vert 2resize ' . ((&columns * 84 + 84) / 169)
tabedit ~/projects/Shade/trunk/include/debug.h
set splitbelow splitright
set nosplitbelow
set nosplitright
wincmd t
set winheight=1 winwidth=1
argglobal
let s:l = 3 - ((2 * winheight(0) + 20) / 41)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
3
normal! 0
lcd ~/projects/Shade/trunk
tabnext 3
if exists('s:wipebuf')
  silent exe 'bwipe ' . s:wipebuf
endif
unlet! s:wipebuf
set winheight=1 winwidth=20 shortmess=filnxtToO
let s:sx = expand("<sfile>:p:r")."x.vim"
if file_readable(s:sx)
  exe "source " . fnameescape(s:sx)
endif
let &so = s:so_save | let &siso = s:siso_save
doautoall SessionLoadPost
unlet SessionLoad
" vim: set ft=vim :
