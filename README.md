Shade - Language of champions!
==============================
(Or rather, it would be if it was finished. Right now it's just sort of a minimal hybrid of C and Go with big plans for the future.)
Installation
------------
`make` to build, `make install` to install.
Lore and Spongy Stuff
---------------------
Shade is a compiler, for a language of my own design. I'm a bit of a programming language snob. I've used most common languages, along with a handful (several handfuls, really) of some not-so-common ones. One of the languages that has influenced me the most is Common Lisp. I really like the language itself, but actually writing code in it feels counterintuitive, due to obscure error messages, no static typing, etc (yes, I'm aware of `declare`, `declaim` and their ilk but the errors are still really bad). One day, after bumbling through another pile of SBCL error messages, I said to myself, "Self, what are you doing still using this language? It's great and powerful and all, but it isn't *fun*.". Taking these words to heart, I searched the myriad languages I had installed at the time for one that had what I was looking for. None of them really fulfilled my requirements, so I made one instead, which still doesn't give me what I want, but it's getting there :-).
Syntax (currently implemented)
------------------------------
* Statements: End with a semicolon, unless the line is the end of a block. The same as C.
* Blocks: `{ [<statement>]* }`. Valid anywhere you can put a statement.
* Constants: The typical syntax. `<integer>` is an integer constant, `"<any characters but ">"` is a string constant.
* Operators: `<expression> <operator> <expression>`. Examples: `1 + 2`, `2 < 5`, `1 + 2 + 3`. Right now, `+`, `-`, `*`, `/`, `==`, `!=`, `<`, `<=`, `>`, and `>=` are implemented.
* Assignment: `<name> = <expression>;`. Example: `x = 1`. Assignments are valid expressions themselves, so you can say `x = y = 1` to set both `x` and `y` to 1.
* Array Assignment: `<name> [<expression>] = <expression>`. Example: `array[3] = 75`. Simple, same semantics as C. Again, array assignments evaluate to the assigned value, so they can be nested.
* Function Calls: `<name> (<expr> [, <expr>]*)`. Examples: `printf("It's as easy as %d %d %d", 1, 2, 3)`. The same as C, essentially.
* Variables: `var <name> -> <type> [, <name> -> <type>]* ;`. Example: `var x -> Integer, y -> Byte;` declares variables `x` and `y` as types `Integer` and `Byte`, respectively.
* Arrays: `var <name> -> <type> [<integer>] ;` Please note that those are literal brackets, rather then denoting an optional syntactic element. Example: `var array -> Integer [10];` declares an array named `array` of 10 integers.
* External Functions: `ext <name> -> <type>;`. Declares a function defined in an external library. Right now, command line option support is nonexistent (I'll mess with getopt in the future, I promise!), so you only link with `libc`, but the support is there. Right now, this essentially lets you say `ext printf -> Integer;` so you can call `printf`.
* Function Declarations: `def <name> [<name> -> <type>]* -> <type> <statement>`. Right now, arguments are VERY buggy. However, functions with no arguments work: `def foo -> Integer { var x -> Integer; x = 1; printf("%d", x); }`. Functions establish their own local namespace: they cannot read nor access global variables. This would lead to a natural use of the functional style if only you could pass arguments. Again, I'm working on it. Expect it very soon.
* Conditionals: `if <expr> <statement>`. Evaluates the first expression, if it isn't equal to zero evaluate the statement. Else blocks coming soon!.
* Loops: `while <expr> <statement>`. Loops as long as the first expression is true, evaluating statement as the loop body.

Example
-------

```
ext printf -> Integer;
ext puts -> Integer;

var y -> Integer, z -> Integer;
var array -> Integer [10];

y = 10;
z = 1;

array[0] = 98;
array[2] = 100;

def f -> Integer {
    var y -> Integer, z -> Integer;
    y = 5;
    z = 0;
    if y == 5 {
        if y != 6 {
            printf("%d %d", y, z);
        }
    }
}

printf("%d %d %d", y, z, array[2]);
f();
printf("%d %d", y, z);
```
License
-------
Shade is licensed under the MIT license (see the "LICENSE" file).
