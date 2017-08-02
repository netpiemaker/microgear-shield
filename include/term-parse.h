/* Serial text command parser */
/* by Chavee Issariyapat */

#ifndef _ATparserH_
#define	 _ATparserH_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>


#define CHAR_A    1
#define FLOAT     21
#define FLOAT_P   22
#define INT       31
#define INT_P     32
#define BOOLA      41
#define BOOL_P    42

#define COUNT_PARMS2(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _, ...) _
#define COUNT_PARMS(...) COUNT_PARMS2(__VA_ARGS__, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1)
#define COMMAND_STOPPER '='
#define ARGUMENT_STOPPER ','
#define MAXARGLENGTH 50

#define CAT(A, B) CAT2(A, B)
#define CAT2(A, B) A ## B

#define TYPEOF(A)\
        __builtin_types_compatible_p(typeof(A), char*) * CHAR_A       \
        + __builtin_types_compatible_p(typeof(A), char[]) * CHAR_A    \
        + __builtin_types_compatible_p(typeof(A), float ) * FLOAT     \
        + __builtin_types_compatible_p(typeof(A), float *) * FLOAT_P  \
        + __builtin_types_compatible_p(typeof(A), int) * INT          \
        + __builtin_types_compatible_p(typeof(A), int*) * INT_P       \
        + __builtin_types_compatible_p(typeof(A), bool) * BOOLA        \
        + __builtin_types_compatible_p(typeof(A), bool*) * BOOL_P

#define scancmd3(I, C, A1) _scancmd(I,C, 1, TYPEOF(A1),A1)
#define scancmd4(I, C, A1,A2) _scancmd(I,C, 2,TYPEOF(A1),A1, TYPEOF(A2),A2)
#define scancmd5(I, C, A1,A2,A3) _scancmd(I,C, 3,TYPEOF(A1),A1, TYPEOF(A2),A2, TYPEOF(A3),A3)
#define scancmd6(I, C, A1,A2,A3,A4) _scancmd(I,C, 4,TYPEOF(A1),A1, TYPEOF(A2),A2, TYPEOF(A3),A3, TYPEOF(A4),A4)
#define scancmd7(I, C, A1,A2,A3,A4,A5) _scancmd(I,C, 5,TYPEOF(A1),A1, TYPEOF(A2),A2, TYPEOF(A3),A3, TYPEOF(A4),A4, TYPEOF(A5),A5)
#define scancmd8(I, C, A1,A2,A3,A4,A5,A6) _scancmd(I,C, 6,TYPEOF(A1),A1, TYPEOF(A2),A2, TYPEOF(A3),A3, TYPEOF(A4),A4, TYPEOF(A5),A5, TYPEOF(A6),A6)

#define scancmd(...) CAT(scancmd, COUNT_PARMS(__VA_ARGS__))(__VA_ARGS__)

int _scancmd(char *input, char *command, int argcount, ...);

#endif
