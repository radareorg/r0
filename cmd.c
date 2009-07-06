/* Copyleft 2009 -- pancake /at/ nopcode /dot/ org */

#define HEXWIDTH 16
void cmd_hexdump(char *arg) {
	unsigned int i, j, len = bsize;
	unsigned char *buf;

	if (*arg) {
		len = (int)str2ull(arg);
		if (len <1)
			len = bsize;
	} 
	buf = malloc(len);
	if (buf == NULL) {
		fprintf(stderr, "Cannot malloc %d bytes.\n", len);
		return;
	}
	io_seek(seek, SEEK_SET);
	len = io_read(buf, len);

	for(i=0;i<len;i+=HEXWIDTH) {
		printf("0x%08llx ", seek+i);
		for(j=i;j<i+HEXWIDTH;j++) {
			if (j>=len) {
				if (j%2) printf("   ");
				else printf("  ");
				continue;
			}
			printf("%02x", buf[j]);
			if (j%2) printf(" ");
		}
		for(j=i;j<i+HEXWIDTH;j++) {
			if (j >= len) printf(" ");
			else printf("%c", isprint(buf[j])?buf[j]:'.');
		}
		printf("\n");
	}
	free(buf);
}

void cmd_bytedump(char *arg) {
	unsigned int i, len = bsize;
	unsigned char *buf;
	if (*arg) {
		len = (int)str2ull(arg);
		if (len <1)
			len = bsize;
	}
	buf = malloc(len);
	if (buf == NULL) {
		fprintf(stderr, "Cannot malloc %d bytes.\n", len);
		return;
	}
	io_seek(seek, SEEK_SET);
	len = io_read(buf, len);
	for(i=0;i<len;i++)
		printf("%02x", buf[i]);
	printf("\n");
}

void cmd_search(char *arg) {
	unsigned char *buf;
	unsigned int i, len, hit=0;

	arg = skipspaces(arg);
	if (*arg=='"') {
		arg++;
		len = strlen(arg)-1;
		arg[len]='\0';
	} else len = hexstr2raw(arg);

	buf = malloc(bsize);
	io_seek(seek, SEEK_SET);
	while(io_read(buf, bsize)>0) {
		for(i=0;i<bsize;i++) {
			if (arg[hit++]!=buf[i])
				hit = 0;
			else if (hit == len)
				printf("0x%llx\n", seek+i-len+1);
		}
		seek+=bsize;
	}
	free(buf);
}

void cmd_bsize(char *arg) {
	if (!*arg)
		printf("%d\n", bsize);
	else if (*arg=='+')
		bsize+=str2ull(arg+1);
	else if (*arg=='-')
		bsize-=str2ull(arg+1);
	else bsize = str2ull(arg);
	if (bsize<1)
		bsize = 1;
}

void cmd_seek(char *arg) {
	if (!*arg)
		printf("%lld\n", seek);
	else if (*arg=='+')
		oseek = seek+=str2ull(arg+1);
	else if (*arg=='-')
		oseek = seek-=str2ull(arg+1);
	else oseek = seek = str2ull(arg);
}

void cmd_write(char *arg) {
	unsigned int len;
	arg = skipspaces(arg);
	if (*arg=='"') {
		arg++;
		len = strlen(arg)-1;
		arg[len]='\0';
	} else len = hexstr2raw(arg);
	io_seek(seek, SEEK_SET);
	io_write(arg, len);
}

void cmd_help(char *arg) {
	if (*arg) {
		ull ret = str2ull(arg);
		printf("0x%llx %lld 0%llo\n", ret, ret, ret);
	} else printf(
	"s[+-addr]     seek to relative or absolute address\n"
	"b[+-size]     change block size\n"
	"w[hex|\"str\"]  change block size\n"
	"/[hex|\"str\"]  search hexpair or string\n"
	"x[size]       hexdump\n"
	"!cmd          run shell command\n"
	"q             quit\n");
}

void cmd_system(char *arg) {
	FILE *f;
	char *buf = malloc(bsize+128);
	int len;
	if (strstr(arg, "BLOCK")) {
		setenv("BLOCK", ".curblk", 1);
		f = fopen(".curblk", "w");
		io_seek(seek, SEEK_SET);
		len = io_read(buf, bsize);
		fwrite(buf, len, 1, f);
		fclose(f);
	}
	if (strstr(arg, "FILE"))
		setenv("FILE", "/bin/ls", 1); // XXX
	if (strstr(arg, "OFFSET")) {
		sprintf(buf, "%lld", seek);
		setenv("OFFSET", buf, 1); // XXX
	}
	if (strstr(arg, "XOFFSET")) {
		sprintf(buf, "0x%llx", seek);
		setenv("XOFFSET", buf, 1); // XXX
	}
	io_system(arg);
	unlink(".curblk");
	free(buf);
}