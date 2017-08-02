#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdint.h"
#define BUFFERSIZE 200
#define MAXARG     10
#define MAXCMDSIZE 16
#define MAXARGSIZE 32

//~ #define uint8_t  unsigned char
//~ #define uint16_t unsigned int

	
        char cmdstopper;
        char argdelimiter;
        char buffer[BUFFERSIZE+1];
        char* argv[MAXARG+1];
        uint8_t argc;

        uint8_t skipSpace(char **p);
        uint8_t parse(char *str);

       void  InitParser();

        char* command();
        char* argString(uint8_t n, char** argv1);
        double argFloat(uint8_t n, char** argv1);
        uint16_t argInt(uint8_t n, char** argv1);

        uint8_t tokenize(char *buffer, char** argv, uint8_t maxarg, char cmdstopper, char argdelimiter);
        uint8_t getArgBoundary(char *p, char **first, char **last);
        
        uint8_t strxcpy2(char *dest, char *src, int n, int max); 
	

