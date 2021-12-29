#ifndef __TYPES_INC_BASICS_H
#define __TYPES_INC_BASICS_H

typedef char         Int8;
typedef short int    Int16;
typedef       int    Int32;
typedef long  int    Int64;
typedef long  double Int128;

typedef unsigned char         UInt8;
typedef unsigned short int    UInt16;
typedef unsigned       int    UInt32;
typedef unsigned long  int    UInt64;

typedef char         Char;
typedef char         Byte;
typedef char*        Str;
typedef char*        Bytes;

typedef float               Float;
typedef double              Double;
typedef void                Void;
typedef void*               Hndl;
typedef void*               Ptr;
typedef enum {False, True}  Bool;

typedef          long  int    SSize;
typedef unsigned long  int    Size;
typedef unsigned long  int    Id;
typedef unsigned long  int    Idx;

#define INVALID_ID    (Id)0
#define INVALID_HNDL  (Hndl)0

#define INF_UINT8  (UInt8)-1
#define INF_UINT16 (UInt16)-1
#define INF_UINT32 (UInt32)-1
#define INF_UINT64 (UInt64)-1

#endif // __TYPES_INC_BASICS_H