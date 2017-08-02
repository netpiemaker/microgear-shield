/* Serial text command parser */
/* by Chavee Issariyapat */

#include "term-parse.h"


float stof(const char* s){
  float rez = 0, fact = 1;
  int point_seen;
  if (*s == '-'){
    s++;
    fact = -1;
  };
  for (point_seen = 0; *s; s++){
    if (*s == '.'){
      point_seen = 1; 
      continue;
    };
    int d = *s - '0';
    if (d >= 0 && d <= 9){
      if (point_seen) fact /= 10.0f;
      rez = rez * 10.0f + (float)d;
    };
  };
  return rez * fact;
};

/* move pointer to the next non-space character */
int trim(char **p) {
    while (**p == ' ') {
        (*p)++;
    }
    if (**p != '\0') return 1;
    else return 0;
}

int strxcpy1(char *dest, char *src, int n, int max) {
    if (strlen(src) <= n) {
        n = strlen(src);
    }
    if (n > max) n = max;
    strncpy(dest,src,n);
    dest[n] = '\0';
    return n;
}

/* cut the comamnd chunk, assume already trimmed */
int extractCommand(char **p, char *chunk, int maxsize) {
    char *h;

    trim(p);
    h = *p;
    while (**p!=COMMAND_STOPPER && **p!='\0') {
        (*p)++;
    }
    strxcpy1(chunk,h,(*p-h)*sizeof(char),maxsize);
    if (**p!='\0') {
        (*p)++;
    }
    return 1;
}

/* cut the argument chunk, assume already trimmed */
int extractChunk(char **p, char *chunk, int maxsize) {
    char *h;
    char insq=0, esc=0;

    if (ARGUMENT_STOPPER == ' ') trim(p);
    h = *p;

    while ((**p!=ARGUMENT_STOPPER || insq)&& **p!='\0') {
        if (**p=='"' && !esc) insq=insq==0?1:0;
        if (**p=='\\') esc=1; else esc=0;
        (*p)++;
    }
    strxcpy1(chunk,h,(*p-h)*sizeof(char),maxsize);
    if (**p!='\0') (*p)++;
    return 1;
}

void getChunkBoundary(char *p, char **first, char **last) {
    *first = p;
    while (**first==ARGUMENT_STOPPER || **first==' ' || **first=='\0') {
        (*first)++;
    }
    *last = p + strlen(p) -1;
    if (*first < *last) {
        while (**last==ARGUMENT_STOPPER || **last==' ' || **last=='\0') {
            (*last)--;
        }
    }
    else {
        *last = *first; 
    }
}

int extractArgument(char **p, char *chunk, int maxsize, char type) {
    int ret, len;
    int nint;
    float nfloat;
    char *f, *l;
    char arg[32];

    ret = extractChunk(p, arg, maxsize);
    getChunkBoundary(arg,&f,&l);

    switch (type) {
        case CHAR_A :
                if (*f=='"') {
                    if (*l=='"') {
                        //strncpy(chunk,f+1,l-f-1); //just copy -- ignore escape characters
                        char* s = f+1;
                        char* t = chunk;
                        while (s < l) {
                            if (*s=='\\') {
                                s++;
                                if (*s=='"' || *s=='\\') *t++ = *s;
                                else if(*s=='n') *t++ = '\n';
                                else if(*s=='t') *t++ = '\t';
                                s++;
                            }
                            else *t++ = *s++;
                        }

                        chunk[l-f] = '\0'; 
                        ret = 1;
                    }
                    else {
                        chunk[0] = '\0';
                        ret = 0;
                    }
                }
                else {
                    strcpy(chunk,arg);
                }
                break;

        case INT :
                *chunk = atoi(arg);
                break;

        case FLOAT :
                *chunk = stof(arg);
                break;

        case BOOLA :
                if (strcmp(arg,"true")==0 || strcmp(arg,"TRUE")==0) *chunk = 1;
                else  *chunk = 0;
                break;
    }
    return ret;
}

int _scancmd(char *input, char *command, int argcount, ...) {
    va_list v;
    va_start(v, argcount);
    int atype,i;
    char *p, *val;

    p = input;
    extractCommand(&p,command,16);
	
    for (i=0;i<argcount;i++) {

        atype = va_arg(v, int);
        val = va_arg(v, char*);

        switch (atype) {
            case CHAR_A :
                    extractArgument(&p, val, MAXARGLENGTH, CHAR_A);
                    break;
            case INT_P :
                    extractArgument(&p, val, MAXARGLENGTH, INT);
                    break;
            case FLOAT_P :
                    extractArgument(&p, val, MAXARGLENGTH, FLOAT); 
                    break;
            case BOOL_P :
                    extractArgument(&p, val, MAXARGLENGTH, BOOLA); 
                    break;
        }
    }
    va_end(v);
    return 0;
}
