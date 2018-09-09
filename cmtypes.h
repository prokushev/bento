/* Container Manager types definitions */
/* Based on Bento Specification Revision 1.0d5 */
/* Author: Yuri Prokushev (C) 2015 */

#ifndef __CM_TYPES__
#define __CM_TYPES__

/* Low-Level types definition */
/* In specification low-level types defined without prefix, but in other parts low-level
   types prefixed with CM_*. This implementation uses only CM_* types */

/* TODO!! Check is OS/2 or SOM types defined and reuse them */

typedef char           CM_CHAR;
typedef CM_CHAR *      CM_PCHAR;
typedef unsigned char  CM_UCHAR;
typedef short          CM_SHORT;
typedef unsigned short CM_USHORT;
typedef long           CM_LONG;
typedef unsigned long  CM_ULONG;

#define TRUE 1
#define FALSE 0

typedef CM_ULONG CMSize;
typedef CM_UCHAR CMBoolean;
typedef CM_PCHAR CMErrorString;  // Error message string pointers.
typedef CM_LONG  CMErrorNbr;     // Error handler error numbers.


#endif /* __CM_TYPES__ */
