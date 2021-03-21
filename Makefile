CC?=gcc
VERSION=0.8
CCw32?=i486-mingw32-gcc
CFLAGS+=-O2 -Wall
#CFLAGS+=-DVERSION=\"${VERSION}\"
PREFIX?=/usr/local
DESTDIR?=

all: r0 bdiff

bdiff: bdiff.o
	${CC} ${CFLAGS} bdiff.o -o bdiff

r0.o: calc.c cmd.c io.c util.c hexparse.c

r0.js:
	emcc -Os -o r0.js r0.c

r0.arm:
	$(CC) -DUSE_DISASM_ARM=1 r0.c -o r0.arm

r0.8086:
	$(CC) -fsanitize=address -g -DUSE_DISASM_8086=1 r0.c -o r0.8086

r0.x86:
	$(CC) -fsanitize=address -g -DUSE_DISASM_X32=1 r0.c -o r0.x86
	# $(CC) -fsanitize=address -g -DUSE_DISASM_X86=1 r0.c -o r0.x86

r0.com: # msdos
	owcc -DUSE_DISASM_X32=1 r0.c -o r0.exe

r0.wasm:
	emcc -Os -o r0.html r0.c

r0.bc:
	clang -emit-llvm -o r0.bc -c r0.c

r0: r0.o
	${CC} ${CFLAGS} r0.o -o r0

dist:
	@if [ -z "${VERSION}" ]; then echo "Try: make dist VERSION=0.5" ; exit 1 ; fi
	git clone . r0-${VERSION}
	rm -rf r0-${VERSION}/.git
	tar czvf r0-${VERSION}.tar.gz r0-${VERSION}
	rm -rf r0-${VERSION}

ios:
	$(MAKE) CC="xcrun --sdk iphoneos gcc -arch arm64 -DHAVE_SYSTEM=0"

ios16:
	$(MAKE) CC="xcrun --sdk iphoneos gcc -arch armv7 -mno-thumb -DHAVE_SYSTEM=0"

ios32:
	$(MAKE) CC="xcrun --sdk iphoneos gcc -arch armv7 -DHAVE_SYSTEM=0"

w32:
	${CCw32} ${CFLAGS} r0.c -o r0.exe

v850:
	./v850.sh

loc:
	@wc -l *.c *.h | grep total

clean:
	rm -f r0 r0.o bdiff bdiff.o
	rm -f r0.x86 r0.arm r0.wasm r0.js

install:
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f r0 ${DESTDIR}${PREFIX}/bin
	cp -f bdiff ${DESTDIR}${PREFIX}/bin
	cp -f vr0 ${DESTDIR}${PREFIX}/bin
	mkdir -p ${DESTDIR}${PREFIX}/share/man/man1
	cp -f r0.1 ${DESTDIR}${PREFIX}/share/man/man1
	cp -f vr0.1 ${DESTDIR}${PREFIX}/share/man/man1

deinstall uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/r0
	rm -f ${DESTDIR}${PREFIX}/bin/vr0
	rm -f ${DESTDIR}${PREFIX}/share/man/man1/r0.1
	rm -f ${DESTDIR}${PREFIX}/share/man/man1/vr0.1
