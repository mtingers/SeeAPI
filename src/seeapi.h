#ifndef SEEAPI_H
#define SEEAPI_H

#include <stdio.h>
#include <stdint.h>
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef struct {
        size_t length;
        char *value;
} str;

enum {
    VAR_U8,
    VAR_U16,
    VAR_U32,
    VAR_U64,
    VAR_I8,
    VAR_I16,
    VAR_I32,
    VAR_I64,
    VAR_STR,
} VAR_TYPES;

typedef struct {
        int type;
        union data {
                u8 _u8;
                u16 _u16;
                u32 _u32;
                u64 _u64;
                i8 _i8;
                i16 _i16;
                i32 _i32;
                i64 _i64;
                str _str;
        };
} SeeApi_Var;

typedef struct {
        size_t length;
        char *value;
} SeeApi_HttpHeader;

typedef struct {
        size_t headers_length;
        SeeApi_HttpHeader *headers;

} SeeApi_Message;

#include "config.h"

#endif // !SEEAPI_H
