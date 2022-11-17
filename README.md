# BAPL (BAd Programming Language)

## Side note
BAPL is a programming language that is designed to be bad. It is a joke language, and is not meant to be taken seriously.
It's a small project I made to just for fun, and will probably get abandoned at some point.

## What is BAPL?
BAPL is supposed to be a mix between C and typescript. It is a compiled language, and is compiled to C, and then compiled to machine code.
It is a statically typed language, and has a lot of features that are not in C, but are in typescript.
more in [syntax](#syntax)


## Syntax 

### Variables
Variables are defined with `var`
Their type is then issued with `::`
```
var::int x = 4;
var::char y = 'a';
var::char* name = "John";
var::bool z = false;
...
```
### Print Statements
Text/variables are printed to the console with `csn <<`
```
csn << "hello world";
```
### Input
Text is inputed from the console via `csn >>`
```
var::int x = none; #undeclared variable
csn >> x;
csn << "X is: " << x;
```
