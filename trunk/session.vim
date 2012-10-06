let SessionLoad = 1
if &cp | set nocp | endif
let s:so_save = &so | let s:siso_save = &siso | set so=0 siso=0
let v:this_session=expand("<sfile>:p")
silent only
cd ~/projects/Shade/trunk
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
set shortmess=aoO
badd +0 ~/projects/Shade/trunk/Makefile
badd +0 ~/projects/Shade/trunk/parser/shade.l
badd +0 ~/projects/Shade/trunk/parser/shade.y
badd +1 ~/projects/Shade/trunk/parser/..
badd +8 ~/projects/Shade/trunk/src
badd +0 ~/projects/Shade/trunk/src/codegen.c
badd +0 ~/projects/Shade/trunk/src/gen.c
badd +0 ~/projects/Shade/trunk/include/gen.h
badd +24 ~/projects/Shade/trunk/src/node.c
badd +33 ~/projects/Shade/trunk/include/node.h
badd +0 ~/projects/Shade/trunk/src/treewalker.c
badd +0 ~/projects/Shade/trunk/include/treewalker.h
badd +0 ~/projects/Shade/trunk/libshade/libshade.cpp
badd +0 ~/projects/Shade/trunk/libshade/shade.asm
silent! argdel *
edit ~/projects/Shade/trunk/Makefile
set splitbelow splitright
set nosplitbelow
set nosplitright
wincmd t
set winheight=1 winwidth=1
argglobal
let s:l = 6 - ((5 * winheight(0) + 20) / 40)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
6
normal! 045l
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
exe 'vert 1resize ' . ((&columns * 84 + 84) / 168)
exe 'vert 2resize ' . ((&columns * 81 + 84) / 168)
argglobal
let s:l = 34 - ((32 * winheight(0) + 20) / 40)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
34
normal! 028l
wincmd w
argglobal
edit ~/projects/Shade/trunk/parser/shade.l
let s:l = 6 - ((5 * winheight(0) + 20) / 40)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
6
normal! 0
wincmd w
exe 'vert 1resize ' . ((&columns * 84 + 84) / 168)
exe 'vert 2resize ' . ((&columns * 81 + 84) / 168)
tabedit ~/projects/Shade/trunk/src/codegen.c
set splitbelow splitright
set nosplitbelow
set nosplitright
wincmd t
set winheight=1 winwidth=1
argglobal
let s:l = 10 - ((9 * winheight(0) + 20) / 40)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
10
normal! 044l
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
exe 'vert 1resize ' . ((&columns * 84 + 84) / 168)
exe 'vert 2resize ' . ((&columns * 81 + 84) / 168)
argglobal
let s:l = 8 - ((7 * winheight(0) + 20) / 40)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
8
normal! 022l
lcd ~/projects/Shade/trunk
wincmd w
argglobal
edit ~/projects/Shade/trunk/src/gen.c
let s:l = 14 - ((13 * winheight(0) + 20) / 40)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
14
normal! 0
lcd ~/projects/Shade/trunk
wincmd w
exe 'vert 1resize ' . ((&columns * 84 + 84) / 168)
exe 'vert 2resize ' . ((&columns * 81 + 84) / 168)
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
exe 'vert 1resize ' . ((&columns * 84 + 84) / 168)
exe 'vert 2resize ' . ((&columns * 81 + 84) / 168)
argglobal
let s:l = 33 - ((25 * winheight(0) + 20) / 40)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
33
normal! 0
lcd ~/projects/Shade/trunk
wincmd w
argglobal
edit ~/projects/Shade/trunk/src/node.c
let s:l = 24 - ((23 * winheight(0) + 20) / 40)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
24
normal! 01l
lcd ~/projects/Shade/trunk
wincmd w
exe 'vert 1resize ' . ((&columns * 84 + 84) / 168)
exe 'vert 2resize ' . ((&columns * 81 + 84) / 168)
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
exe 'vert 1resize ' . ((&columns * 84 + 84) / 168)
exe 'vert 2resize ' . ((&columns * 81 + 84) / 168)
argglobal
let s:l = 6 - ((5 * winheight(0) + 20) / 40)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
6
normal! 017l
lcd ~/projects/Shade/trunk
wincmd w
argglobal
edit ~/projects/Shade/trunk/src/treewalker.c
let s:l = 169 - ((33 * winheight(0) + 20) / 40)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
169
normal! 046l
lcd ~/projects/Shade/trunk
wincmd w
exe 'vert 1resize ' . ((&columns * 84 + 84) / 168)
exe 'vert 2resize ' . ((&columns * 81 + 84) / 168)
tabedit ~/projects/Shade/trunk/libshade/shade.asm
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
set nosplitbelow
set nosplitright
wincmd t
set winheight=1 winwidth=1
exe 'vert 1resize ' . ((&columns * 84 + 84) / 168)
exe 'vert 2resize ' . ((&columns * 81 + 84) / 168)
argglobal
let s:l = 84 - ((19 * winheight(0) + 20) / 40)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
84
normal! 08l
lcd ~/projects/Shade/trunk
wincmd w
argglobal
edit ~/projects/Shade/trunk/libshade/libshade.cpp
let s:l = 126 - ((19 * winheight(0) + 20) / 40)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
126
normal! 032l
lcd ~/projects/Shade/trunk
wincmd w
exe 'vert 1resize ' . ((&columns * 84 + 84) / 168)
exe 'vert 2resize ' . ((&columns * 81 + 84) / 168)
tabnext 1
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
