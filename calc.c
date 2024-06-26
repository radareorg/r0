/* ported to C by pancake for r2 in 2012-2013 */
// TODO: integrate floating point support
// TODO: do not use global variables
/*
   Reference Chapter 6:
   "The C++ Programming Language", Special Edition.
   Bjarne Stroustrup,Addison-Wesley Pub Co; 3 edition (February 15, 2000) 
    ISBN: 0201700735 
 */

#include <ctype.h>
#include <stdio.h>
#include <unistd.h>

#define R_API 
#define R_NUMCALC_STRSZ 4096

typedef struct {
	double d;
	ut64 n;
} RNumCalcValue;
typedef enum {
	RNCNAME, RNCNUMBER, RNCEND, RNCINC, RNCDEC,
	RNCPLUS='+', RNCMINUS='-', RNCMUL='*', RNCDIV='/',
	//RNCXOR='^', RNCOR='|', RNCAND='&',
	RNCPRINT=';', RNCASSIGN='=', RNCLEFTP='(', RNCRIGHTP=')'
} RNumCalcToken;

typedef struct r_num_calc_t {
	RNumCalcToken curr_tok;
	RNumCalcValue number_value;
	char string_value[R_NUMCALC_STRSZ];
	int errors;
	char oc;
	const char *calc_err;
	int calc_i;
	const char *calc_buf;
	int calc_len;
} RNumCalc;


typedef struct r_num_t {
	ut64 (*callback)(struct r_num_t *userptr, const char *str, int *ok);
//	RNumCallback callback;
	ut64 value;
	double fvalue;
	void *userptr;
	RNumCalc nc;
} RNum;
/* accessors */
static inline RNumCalcValue Nset(ut64 v) { RNumCalcValue n; n.d = (double)v; n.n = v; return n; }
static inline RNumCalcValue Nsetf(double v) { RNumCalcValue n; n.d = v; n.n = (ut64)v; return n; }
static inline RNumCalcValue Naddf(RNumCalcValue n, double v) { n.d += v; n.n += (ut64)v; return n; }
static inline RNumCalcValue Naddi(RNumCalcValue n, ut64 v) { n.d += (double)v; n.n += v; return n; }
static inline RNumCalcValue Nsubi(RNumCalcValue n, ut64 v) { n.d -= (double)v; n.n -= v; return n; }
static inline RNumCalcValue Nadd(RNumCalcValue n, RNumCalcValue v) { n.d += v.d; n.n += v.n; return n; }
static inline RNumCalcValue Nsub(RNumCalcValue n, RNumCalcValue v) { n.d -= v.d; n.n -= v.n; return n; }
static inline RNumCalcValue Nmul(RNumCalcValue n, RNumCalcValue v) { n.d *= v.d; n.n *= v.n; return n; }
static inline RNumCalcValue Ndiv(RNumCalcValue n, RNumCalcValue v) {
	if (v.d) n.d /= v.d; else n.d = 0;
	if (v.n) n.n /= v.n; else n.n = 0;
	return n;
}

static RNumCalcValue expr(RNum*, RNumCalc*, int);
static RNumCalcValue term(RNum*, RNumCalc*, int);
static void error(RNum*, RNumCalc*, const char *);
static RNumCalcValue prim(RNum*, RNumCalc*, int);
static RNumCalcToken get_token(RNum*, RNumCalc*);

static void error(RNum *num, RNumCalc *nc, const char *s) {
	nc->errors++;
	nc->calc_err = s;
	//fprintf (stderr, "error: %s\n", s);
}

static RNumCalcValue expr(RNum *num, RNumCalc *nc, int get) {
	RNumCalcValue left = term (num, nc, get);
	for (;;) {
		if (nc->curr_tok == RNCPLUS)
			left = Nadd (left, term (num, nc, 1));
		else if (nc->curr_tok == RNCMINUS)
			left = Nsub (left, term (num, nc, 1));
		else break;
	}
	return left;
}

static RNumCalcValue term(RNum *num, RNumCalc *nc, int get) {
	RNumCalcValue left = prim (num, nc, get);
	for (;;) {
		if (nc->curr_tok == RNCMUL) {
			left = Nmul (left, prim (num, nc, 1));
		} else
		if (nc->curr_tok == RNCDIV) {
			RNumCalcValue d = prim (num, nc, 1);
			if (!d.d) {
				error (num, nc, "divide by 0");
				return d;
			}
			left = Ndiv (left, d);
		} else return left;
	}
}

static RNumCalcValue prim(RNum *num, RNumCalc *nc, int get) {
	char *p;
	RNumCalcValue v = {0};
	if (get) get_token (num, nc);
	switch (nc->curr_tok) {
	case RNCNUMBER:
		v = nc->number_value;
		get_token (num, nc);
		return v;
	case RNCNAME:
		for(p=nc->string_value;*p&&*p==' ';p++) {};
		v = Nset (str2ut64 (nc->string_value));
		get_token (num, nc);
		if (nc->curr_tok  == RNCASSIGN) 
			v = expr (num, nc, 1);
		if (nc->curr_tok == RNCINC) Naddi (v, 1);
		if (nc->curr_tok == RNCDEC) Nsubi (v, 1);
		return v;
	case RNCINC: return Naddi (prim (num, nc, 1), 1);
	case RNCDEC: return Naddi (prim (num, nc, 1), -1);
	case RNCMINUS: return Nsub (v, prim (num, nc, 1));
	case RNCLEFTP:
		v = expr (num, nc, 1);
		if (nc->curr_tok == RNCRIGHTP)
			get_token (num, nc);
		else error (num, nc, " ')' expected");
	case RNCEND:
	case RNCPLUS:
	case RNCMUL:
	case RNCDIV:
	case RNCPRINT:
	case RNCASSIGN:
	case RNCRIGHTP:
		return v;
	//default: error (num, nc, "primary expected");
	}
	return v;
}

static void cin_putback (RNum *num, RNumCalc *nc, char c) {
	nc->oc = c;
}

R_API const char *r_num_calc_index(RNum *num, const char *p) {
	if (num == NULL)
		return NULL;
	if (p) {
		num->nc.calc_buf = p;
		num->nc.calc_len = strlen (p);
		num->nc.calc_i = 0;
	}
	//if (num->nc.calc_i>num->nc.calc_len) return NULL;
	return num->nc.calc_buf + num->nc.calc_i;
}

static int cin_get(RNumCalc *nc, char *c) {
	if (nc->oc) {
		*c = nc->oc;
		nc->oc = 0;
	} else {
		if (!nc->calc_buf)
			return 0;
		//if (nc->calc_i>nc->calc_len) return 0;
		*c = nc->calc_buf[nc->calc_i];
		if (*c) nc->calc_i++;
		else return 0;
	}
	return 1;
}

static int cin_get_num(RNum *num, RNumCalc *nc, RNumCalcValue *n) {
	char c, str[R_NUMCALC_STRSZ];
	double d;
	int i = 0;
	str[0] = 0;
	while (cin_get (nc, &c)) {
		if (c!=':' && c!='.' && !isalnum (c)) {
			cin_putback (num, nc, c);
			break;
		}
		if (i<R_NUMCALC_STRSZ)
			str[i++] = c;
	}
	str[i] = 0;
	*n = Nset (str2ut64 (str));
	if (*str>='0' && *str<='9' && strchr (str, '.')) {
		if (sscanf (str, "%lf", &d)<1)
			return 0;
		*n = Nsetf (d);
	}
#if 0
// XXX: use r_num_get here
	if (str[0]=='0' && str[1]=='x') {
		ut64 x = 0;
		if (sscanf (str+2, "%llx", &x)<1)
			return 0;
		*n = Nset (x);
	} else
	if (strchr (str, '.')) {
		if (sscanf (str, "%lf", &d)<1)
			return 0;
		*n = Nsetf (d);
	} else {
		ut64 u;
		if (sscanf (str, "%"PFMT64d, &u)<1)
			return 0;
		*n = Nset (u);
	}
#endif
	return 1;
}

static RNumCalcToken get_token(RNum *num, RNumCalc *nc) {
	char ch = 0, c = 0;

	do { if (!cin_get (nc, &ch)) return nc->curr_tok = RNCEND;
	} while (ch!='\n' && isspace (ch));

	switch (ch) {
	case 0:
	case ';':
	case '\n':
		return nc->curr_tok = RNCEND;
	case '+':    // added for ++name and name++
		if (cin_get (nc, &c) && c == '+')
			return nc->curr_tok = RNCINC;
		cin_putback (num, nc, c);
		return nc->curr_tok = (RNumCalcToken) ch;
	case '-':
		if (cin_get (nc, &c) && c == '-')
			return nc->curr_tok = RNCDEC;
		cin_putback (num, nc, c);
		return nc->curr_tok = (RNumCalcToken) ch;
	case '*':
	case '/':
	case '(':
	case ')':
	case '=':
		return nc->curr_tok = (RNumCalcToken) ch;
	case '0':case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
	case '.':
		cin_putback (num, nc, ch);
		if (!cin_get_num (num, nc, &nc->number_value)) {
			error (num, nc, "invalid number conversion");
			return 1;
		}
		return nc->curr_tok = RNCNUMBER;
	default:
#define isvalidchar(x) \
	(isalnum(x) || x==':' || x=='$' || x=='.' || x=='_' || x=='?' || x=='\\' \
	|| x==' ' || x=='[' || x==']' || x=='}' || x=='{' || x=='/' || (x>='0'&&x<='9'))
{
			int i = 0;
			nc->string_value[i++] = ch;
			if (ch == '[') {
				while (cin_get (nc, &ch) && ch!=']') {
					if (i>=R_NUMCALC_STRSZ) {
						error (num, nc, "string too long");
						return 0;
					}
					nc->string_value[i++] = ch;
				}
				nc->string_value[i++] = ch;
			} else {
				while (cin_get (nc, &ch) && isvalidchar (ch)) {
					if (i>=R_NUMCALC_STRSZ) {
						error (num, nc, "string too long");
						return 0;
					}
					nc->string_value[i++] = ch;
				}
			}
			nc->string_value[i] = 0;
			cin_putback (num, nc, ch);

			return nc->curr_tok = RNCNAME;
}
		//}
		error (num, nc, "bad token");
		return nc->curr_tok = RNCPRINT;
	}
}

static void load_token(RNum *num, RNumCalc *nc, const char *s) {
	nc->calc_i = 0;
	nc->calc_len = 0;
	nc->calc_buf = s;
	nc->calc_err = NULL;
}

R_API ut64 r_num_calc(RNum *num, const char *str, const char **err) {
	RNumCalcValue n;
	RNumCalc *nc, nc_local;
	if (!str || !*str)
		return 0LL;

	if (num == NULL)
		nc = &nc_local;
	else nc = &num->nc;

	/* init */
	nc->curr_tok = RNCPRINT;
	nc->number_value.d = 0.0;
	nc->number_value.n = 0LL;
	nc->errors = 0;
	nc->oc = 0;
	nc->calc_err = NULL;
	nc->calc_i = 0;
	nc->calc_len = 0;
	nc->calc_buf = NULL;

	load_token (num, nc, str);
	get_token (num, nc);
	n = expr (num, nc, 0);
	if (err) *err = nc->calc_err;
	//if (nc->curr_tok == RNCEND) return 0LL; // XXX: Error
	//if (nc->curr_tok == RNCPRINT) //return 0LL; // XXX: the fuck
	//	n = expr (num, nc, 0);
	if (n.d != ((double)(ut64)n.d)) {
		if (num) num->fvalue = n.d;
	} else if (num) num->fvalue = (double)n.n;
	return n.n;
}

R_API ut64 calc(const char *str) {
	return r_num_calc (NULL, str, NULL);
}

