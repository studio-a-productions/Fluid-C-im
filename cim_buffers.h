#ifndef CIM_BUFFERS_H
#define CIM_BUFFERS_H

#include "common_libs.h"
#include "cim_math.h"
/*
    If you want to have cim_math support, include it before this header.
    Originally some of these functions were in cim_math, but we've 
        decided to become sane.
*/

#define EMPTY_BUFFER {NULL, 0}

#define G_CREATE_BUFFER(a, b, c) \
    do { \
        (a).data = SDL_malloc((b)*(c)); \
        (a).size = (b); \
    } while (0)
#define G_RESIZE_BUFFER(a,b,c) \
    do { \
        (a).data = SDL_realloc(&(a), (b)*(c)); \
        (a).size = (b); \
    } while (0)


typedef struct buffer_string {
    char **data;
    size_t size;
} buffer_string;

typedef struct buffer_float {
    float*data;
    size_t size;
} buffer_float;

typedef struct buffer_int {
    int32_t*data;
    size_t size;
} buffer_int;
typedef struct buffer_intt8 {
    int8_t*data;
    size_t size;
} buffer_intt8;
typedef struct buffer_intt16 {
    int16_t*data;
    size_t size;
} buffer_intt16;

typedef struct buffer_uint {
    uint32_t*data;
    size_t size;
} buffer_uint;
typedef struct buffer_uintt8 {
    uint8_t* data;
    size_t size;
} buffer_uintt8;
typedef struct buffer_uintt16 {
    uint16_t*data;
    size_t size;
} buffer_uintt16;


typedef struct stored_string {
    const size_t index;
    buffer_string*storage;
} stored_string;

typedef struct stored_float {
    const size_t index;
    buffer_float* storage;
} stored_float;

typedef struct stored_uintt8 {
    const size_t index;
    buffer_uintt8* storage;
} stored_uintt8;


buffer_string Create_StringBuf(const size_t); // (number of elements, initial size of elements)
stored_string Store_String(buffer_string* const buff, const size_t, const char*);
char* Get_String(buffer_string*const buff, const size_t);
void Set_String(buffer_string *const buff, const size_t, const char*);
void Resize_StringBuf(buffer_string*const buff, const size_t);
void Free_StringBuf(buffer_string* buff);

buffer_float Create_FloatBuf(const size_t);
stored_float Store_Float(buffer_float*const buff, const size_t, const float val);
float Get_Float(buffer_float*const buff, const size_t);
void Set_Float(buffer_float*const buff, const size_t, const float val); // If you need to pass '&', just use "[indx]" or the macro
void Resize_FloatBuf(buffer_float*const buff, const size_t);
void Free_FloatBuf(buffer_float* buff);

buffer_uintt8 Create_UIntt8Buf(const size_t);
stored_uintt8 Store_UIntt8(buffer_uintt8*const buff, const size_t, const uint8_t val);
uint8_t Get_UIntt8(buffer_uintt8*const buff, const size_t);
void Set_UIntt8(buffer_uintt8*const buff, const size_t, const uint8_t val); // If you need to pass '&', just use "[indx]" or the macro
void Resize_UIntt8Buf(buffer_uintt8*const buff, const size_t);
void Free_UIntt8Buf(buffer_uintt8* buff);

typedef struct buffer_float2 {
    float*data;
    size_t size;
} buffer_float2;
typedef struct buffer_float3 {
    float *data;
    size_t size;
} buffer_float3;
typedef struct buffer_float4 {
    float *data;
    size_t size;
} buffer_float4;


typedef struct stored_float2 {
    const size_t index;
    buffer_float2* storage;
} stored_float2;
typedef struct stored_float3{
    const size_t index;
    buffer_float3* storage;
} stored_float3;
typedef struct stored_float4{
    const size_t index;
    buffer_float4* storage;
} stored_float4;

buffer_float2 Create_Float2Buf(const size_t); // always check your .data
buffer_float3 Create_Float3Buf(const size_t); // always check your .data
buffer_float4 Create_Float4Buf(const size_t); // always check your .data

void Set_Float2(buffer_float2*const buff, const size_t, const float2 val);
void Set_Float3(buffer_float3*const buff, const size_t, const float3 val);
void Set_Float4(buffer_float4*const buff, const size_t, const float4 val);

float2 Get_Float2(buffer_float2*const buff, const size_t);
float3 Get_Float3(buffer_float3*const buff, const size_t);
float4 Get_Float4(buffer_float4*const buff, const size_t);

float2 Deref_Float2(float*const p);
float3 Deref_Float3(float*const p);
float4 Deref_Float4(float*const p);

stored_float2 Store_Float2(buffer_float2*const buff, const size_t, const float2);
stored_float3 Store_Float3(buffer_float3*const buff, const size_t, const float3);
stored_float4 Store_Float4(buffer_float4*const buff, const size_t, const float4);

void Resize_Float2Buf(buffer_float2*const buff, const size_t);
void Resize_Float3Buf(buffer_float3*const buff, const size_t);
void Resize_Float4Buf(buffer_float4*const buff, const size_t);

void Free_Float2Buf(buffer_float2* buff);
void Free_Float3Buf(buffer_float3* buff);
void Free_Float4Buf(buffer_float4* buff);


#endif