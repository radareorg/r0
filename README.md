# R0 stands for radare-zero

[![ci](https://github.com/radareorg/r0/actions/workflows/ci.yml/badge.svg)](https://github.com/radareorg/r0/actions/workflows/ci.yml)

r0 aims to be a minimalistic reimplementation of the radare shell
without much complexity and relaying all the extensibility to external
applications trying to keep the source as small as possible.

## Features

* Small footprint (50KB)
* Minimalistic Intel and ARM disassemblers (90KB)
* Minimum set of commands to inspect and manipulate binaries
* r0d does binary diffing and patching files
* r0v is the visual interactive frontend of r0
* Very portable: Compiles for wasm, js.. even for MS-DOS!
* Single binary without any external dependency

## AUTHOR
* pancake<nopcode.org>

## COMMANDS

```
[0x00000000]> ?
s[+-addr]     seek to relative or absolute address
b[+-size]     change block size
w[hex|"str"]  write hexpair or string
/[hex|"str"]  search hexpair or string
x[size]       hexdump
d[size]       disassemble n bytes
X[size]       hexpair dump
p[fmt]        print formatted current block ('p' for help)
d[size]       disasemble
r[+-[num]]    truncate or -remove N bytes
.[file]       interpret file
<[file]       load file in current seek
>[file]       dump current block to file
!cmd          run shell command
?expr         calculate numeric expression
q             quit
[0x00000000]>
```

WORK IN PROGRESS
================
print command

```
[0x00000000]> p?
ob/wW/dD/qQ  byte (oct,hex), word, dword, qword (lil, big endian)
i/I/f/F      int32 (lil, big), float (lil, big)
s/S          short int16 (lil, big)
z/Z          zero-terminatted string (ascii, wide-ascii)
./:/*        skip 1 or 4 chars, repeat last format instead of cycle
```

PORTABILITY
===========
r0 is known to build and run on several OS.
- GNU/Hurd, Plan9, DOS, BSD, Solaris, Linux, macOS, Windows, Wasm, Javascript, ...

TODO:
=====
- support for escapped characters in string write and search ops
- Add support for simple math ops (+,-,*,/) no parenthesis plz :)

TODO/TOTHINK
============
- Remove '.' command? to make it suck less
- Add .! command that runs !foo > file and then .file
- Support for multiple commands in a single line (';' separator)
