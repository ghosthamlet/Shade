Shade - Language of champions!
==============================

Shade is a compiled, [semi-]functional language that runs on x86.

Exciting things (really, advantages over C):
* Compiles to nice, *readable*, x86 assembly code (Intel syntax)!
* First-class functions, which opens the way for a nice standard library using higher-order programming.
* Nested function definitions, local functions.
* Easy interop with C, with type checking (a module system is on the way!)
* Static types, with a consistent postorder type syntax. For example, `x -> Integer` rather than `int x`. Some may complain about the more verbose type syntax, but to that my argument is that you really shouldn't be spending most of your time declaring variables, and if you are, you probably need to reevaluate your design :P)

Current limitations:
* There is no optimizer (but there will be soon: I'm gradually working through *Advanced Compiler Design and Implementation*.
* No object model now, but that will change once I implement language-level hash tables (with syntactic sugar, because the lack of easily available hash maps is one of the main things I find annoying in C. Think Python style `{}`).
* Still under rather heavy development.

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
* Function Declarations: `def <name> [<name> -> <type>]* -> <type> <statement>`. `def foo (arg -> Integer) -> Void { var x -> Integer; x = 1; printf("%d", arg + x); }`.
* Conditionals: `if <expr> <statement>`. Evaluates the first expression, if it isn't equal to zero evaluate the statement. Else blocks coming soon!.
* Loops: `while <expr> <statement>`. Loops as long as the first expression is true, evaluating statement as the loop body.

Example
-------

```
ext printf -> Void;
ext puts -> Void;

var y -> Integer, z -> Integer;
var array -> Integer [10];
var func -> (arg1 -> Integer, arg2 -> Integer) -> Integer;

y = 10;
z = 1;

array[0] = 98;
array[2] = 100;

var string -> Byte [10];
string = "bluhbluh";

def f (arg1 -> Integer, arg2 -> Integer) -> Integer {
    ext printf -> Void;
    var y -> Integer, z -> Integer, a -> Integer;
    y = 5;
    z = 0;
    a = 15;
    if y == 5 {
        printf("%d %d %d %d %d", y, z, a, arg1, arg2);
        if z {
	    printf("Nope!");
	}
    }
}

func = f;

printf("%d %d %d %d", y, z, array[0], array[2]);
func(y, z);
printf("%d %d", y, z);
puts(string);
```

License
-------
Shade is licensed under the MIT license (see the "LICENSE" file).
