while : ; do
	rm -f r0.x86
	gcc -DUSE_DISASM_X32=1 -flto -O3 r0.c -o r0.x86
	strip r0.x86
	ls -l r0.x86
	sleep 1
done
