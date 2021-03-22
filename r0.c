/* MIT 2009-2021 -- pancake /at/ nopcode /dot/ org */

#define ut64 unsigned long long 
#define ut8 unsigned char

static int earlyquit = 0;
static int verbose = 1;
static int scriptn = 0;
static const char **scripts = 0;
static int cmdn = 0;
static char **cmds = 0;
static ut64 oldseek, curseek = 0LL;
static int obsize, bsize = 256;
static int red_cmd(char *cmd); // XXX : recursive depenency
#if defined(__WATCOMC__)
#define HAVE_FTRUNCATE 0
#define BUFSZ 1024
#else
#define BUFSZ 128*1024
#endif

#include "r0.h"
#include "util.c"
#include "calc.c"
#include "cmd.c"

static void red_slurpin() {
	ut8 buf[BUFSZ];
	for(;;) {
		int len = read(0, buf, sizeof(buf));
		if(len<1) break;
		hexdump(buf, len, 16);
		curseek += len;
	}
}

static int red_interpret(const char *file) {
	char buf[BUFSZ];
	FILE *fd = fopen(file, "r");
	if(fd != NULL) {
		for(;;) {
			if(fgets(buf, sizeof(buf), fd) == NULL)
				break;
			red_cmd(buf);
		}
		fclose(fd);
	} else if (file)
		fprintf(stderr, "Cannot open script file '%s'\n", file);
	return 1;
}

static int red_cmd(char *cmd) {
	char *arg = cmd+1;
	SKIPSPACES(arg);
	switch(*cmd) {
	case 'q': return 0;
	case ';': case '#': break; // comment
	case '>': return cmd_dump(arg); break;
	case '<': return cmd_load(arg); break;
	case '.': return red_interpret(arg); break;
	case 's': return cmd_seek(arg); break;
	case 'b': return cmd_bsize(arg); break;
	case '/': return cmd_search(arg); break;
#if USE_DISASM 
	case 'd': return cmd_disasm(arg); break;
#else
	case 'd': return cmd_system("echo X | r0 -n $BLOCK | rasm2 -o $OFFSET -D - |head -n $(($LINES-1))");
#endif
	case 'p': return cmd_print(arg); break;
	case 'r': return cmd_resize(arg); break;
	case 'x': return cmd_hexdump(arg); break;
	case 'X': return cmd_bytedump(arg); break;
	case 'w': return cmd_write(arg); break;
	case '!': return cmd_system(arg); break;
	case 'V': return cmd_system("vr0 $FILE"); break;
	case '?': return cmd_help(arg); break;
	default: fprintf(stderr, "? %s\n", cmd);
	}
	return 1;
}

static int red_prompt() {
	char *at, *at2, line[BUFSZ];
	if(verbose) {
		printf("[0x%08"LLF"x]> ", curseek);
		fflush(stdout);
	}
	if(fgets(line, sizeof(line), stdin) == NULL)
		return 0;
	line[strlen(line)-1] = '\0';
	if(*line != '!') {
		at = strchr(line, '@');
		oldseek = curseek;
		obsize = bsize;
		if(at) {
			*at = 0;
			at2 = strchr(++at, ':');
			if(at2) {
				*at2 = 0; at2++;
				if(*at2) bsize = (int)str2ut64(at2);
			}
			if(*at) curseek = str2ut64(at);
		}
	}
	at = line;
	SKIPSPACES(at);
	return red_cmd(at);
}

static int r0_open(const char *file) {
	int ret = io_open(file);
	if(ret != -1) {
		oldseek = 0;
		setenv("FILE", file, 1);
		if(scripts)
			for (ret=0;ret<scriptn;ret++)
				red_interpret(scripts[ret]);
		if(cmds)
			for (ret=0;ret<cmdn;ret++)
				red_cmd(cmds[ret]);
		if(earlyquit)
			return 0;
		while((ret=red_prompt())>0) {
			curseek = oldseek;
			bsize = obsize;
		}
		io_close();
	} else if (file)
		fprintf(stderr, "Cannot open '%s'\n", file);
	return ret==-1 ?1:0;
}

static int red_help() {
	puts("r0 [-qhnv] [-c cmd] [-i script] [-|file ..]");
	return 0;
}

int main(int argc, char **argv) {
	int i, ret = 1;
	argc++;
	cmdn = 0;
	scriptn = 0;
	scripts = malloc(sizeof(const char*)*argc);
	cmds = malloc(sizeof(const char*)*argc);
	if(argc>1 && argv[1]) {
		for(i=1; i<argc; i++) {
			if(argv[i] && argv[i][0]=='-')
				switch(argv[i][1]) {
				case 'q': earlyquit = 1; break;
				case 'i': scripts[scriptn++] = argv[++i]; break;
				case 'c': cmds[cmdn++] = argv[++i]; break;
				case 'n': verbose = 0; break;
				case 'v': puts(VERSION); ret = 0; break;
				case 'h': ret = red_help(); break;
				case 0x0: red_slurpin(); ret = 0; break;
			} else {
				if (!argv[i]) break;
				ret = r0_open(argv[i]);
			}
		}
	} else {
		ret = red_help();
	}
	free(scripts);
        return ret;
}
