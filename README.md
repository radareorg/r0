R0 stands for the independent raw editor
==========================================

red aims to be a minimalistic reimplementation of the radare shell
without much complexity and relaying all the extensibility to external
applications trying to keep the source as small as possible.

AUTHOR
------
	pancake<nopcode.org>

COMMANDS
========

	? is for help   get help or evaluate numeric expression
	/ search        search strings or hexpairs
	!cmd            run command from shell
	x hexdump       hexdump
	X dword dump    hexpair dump
	> file          dump current block to file
	< file          slurp file into current block
	w "string\x00"  write string
	w 023839400     write hexpairs
	b 30            set block size
	s addr          seek address
	r [size|-rmv]   get filesize, truncate file to size, or -remove bytes
	p [bwWdDqQiIF.] print formatted the current block
	q               quit


WORK IN PROGRESS
================
print command
	b/w/d/q   byte, word, dword, qword (little endian)
	B/W/D/Q   byte, word, dword, qword (big endian)
	i/I/f/F   int32 (lil, big), float (lil, big)
	z/Z       zero-terminatted strings (ascii, widechar)
	./:       skip 1 or 4 chars
	*         repeat last value until death

PORTABILITY
===========
r0 is known to build and run on several OS.
- GNU, Linux, OSX, Windows (mingw), cygwin, Solaris, BSD, ...

TODO:
=====
- support for escapped characters in string write and search ops
- Add support for simple math ops (+,-,*,/) no parenthesis plz :)

TODO/TOTHINK
============
- Remove '.' command? to make it suck less
- Add .! command that runs !foo > file and then .file
- Support for multiple commands in a single line (';' separator)
