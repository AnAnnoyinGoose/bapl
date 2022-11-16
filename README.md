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
Variables are declared with the `var` keyword, their type is assinged with a `::` and their value is assigned with a `=`. 
```bapl
var::int x = 5
var::string y = "Hello World"
var::bool z = true
var::float  a= 5.5
var::char b = 'a'
```
### Referencing variables
Variables can be referenced by using the `$` symbol, and then the variable name.
```bapl
var::int x = 5
var::int y = $x
```
### Functions
Functions are declared with the `func` keyword, their name is assigned with a `::` and their parameters are assigned with a `(` and `)`. 
```bapl
func main::void() {
    cnsl << "Hello World";
}
```
### If statements
If statements are declared with the `if` keyword, their condition is assigned with a `(` and `)`, and their body is assigned with a `{` and `}`. 
```bapl
if (true) {
    cnsl << "Hello World";
}
```
### loops
Loops are declared with the `loop` keyword, the type of loop is assigned with a `::` and their body is assigned with a `{` and `}`. 
```bapl
loop::while(true) {
    cnsl << "Hello World";
}
``` 
### Re declarations
Re declarations are declared with the `!` keyword, their value is assigned with a `=`. 
```bapl
!x = 5
```


