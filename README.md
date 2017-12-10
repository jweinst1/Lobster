# Lobster

![Image of Lobster](https://www.mainelobsternow.com/images/live_lobster.jpg)

*An expression-based, binary nesting language*

`Lobster` is a prototype of a nested programming language (Lisp-like), that can be evaluated as pure expressions. 
The advantage of `Lobster` is the speed and small size at which it can be embedded or used in other applications.

## Usage

`Lobster` is a single header embeddable language. However you can build it into an executable by running this command

```
$ make all
```

Then, you can compile snippets of code like so

```
$ ./bin/Lobster "+(8 5 -(9 9))"
13
```

To Use Lobster in your application or program, just use the `Lobster.h` file.

## Goals

The goals of the Lobster Language, despite being quite small, is to prove a different method of evaluation for nested structures in programs, and to greatly decrease the complexity associated with runtimes, virtual machines, and such.

Specifically, `Lobster` aims to tackle the following issues:

> 1. Eliminate the use of AST's, Parsers, Tokens and runtimes.
> 2. Direct translation from source code to bytecode.
> 3. Evaluation of instructions in linear O(n) time.

Lobster accomplishes this via *direct translation* instead of traditional tokenization, parsing, code generation etc.

Example:

```
+ ( 5 4 )
|  || ||
[Add, Start, int, {binary}, int, {binary}, End]
```


## License

`Lobster` is MIT licensed and open source.

