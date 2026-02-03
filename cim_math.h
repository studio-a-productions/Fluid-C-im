#ifndef CIM_MATH_H
#define CIM_MATH_H

#include <stdio.h>
#include <SDL.h>
#include "cim_environment.h"

#define ADD(a, b) ((a)+(b))
#define ADD3(a, b, c) ((a) + (b) + (c))
#define SUB(a, b) ((a)-(b))
#define MULT(a, b) ((a)*(b))
#define DIV(a, b) ((a)/(b))
#define SQUARE(a) ((a)*(a))


// --- float_  operations ---
// ++  buffer_float_ oppr  ++ 

#define EDIT_FLOAT2(a,b,c) \
    do { \
        (a).x=(b); \
        (a).y=(c); \
    } while (0)
#define EDIT_FLOAT3(a,b,c,d) \
    do { \
        (a).x=(b); \
        (a).y=(c); \
        (a).z=(d); \
    } while (0)
#define EDIT_FLOAT4(a,b,c,d,e) \
    do { \
        (a).x=(b); \
        (a).y=(c); \
        (a).z=(d); \
        (a).w=(e); \
    } while (0)
#define SET_FLOAT(a, b, c) (a).data[b] = (c);
#define SET_FLOAT2(a, b, c) \
    do { \
        (a).data[b*2] = (c).x; \
        (a).data[MULT(b,2)+1] = (c).y; \
    } while (0)
#define SET_FLOAT3(a, b, c) \
    do { \
        (a).data[MULT(b,3)] = (c).x; \
        (a).data[MULT(b,3)+1] = (c).y; \
        (a).data[MULT(b,3)+2] = (c).z; \
    } while (0)
#define SET_FLOAT4(a, b, c) \
    do { \
        (a).data[MULT(b, 4)] = (c).x; \
        (a).data[MULT(b, 4)+1] = (c).y; \
        (a).data[MULT(b, 4)+2] = (c).z; \
        (a).data[MULT(b, 4)+3] = (c).w; \
    } while (0)
#define GET_FLOAT(a, b) (a).data[b]
#define GET_FLOAT2(a, b) { \
    (a).data[b*2], \
    (a).data[b*2+1]}
#define GET_FLOAT3(a, b) { \
    (a).data[b*3], \
    (a).data[b*3+1], \
    (a).data[b*3+2]}
#define GET_FLOAT4(a, b) { \
    (a).data[MULT(b,4)], \
    (a).data[MULT(b,4)+1], \
    (a).data[MULT(b,4)+2], \
    (a).data[MULT(b,4)+3]}



#define NORMALIZE_TYPE(a, b, c) \
    (a) = ((a) < (b)) ? (0.0F) : (((a) > (c)) ? 1.0F : ((a)-(b))/(float)((c)-(b)))
#define NORMALIZE_FORTYPE(a, b, c) \
    ((a) < (b)) ? (0.0F) : (((a) > (c)) ? 1.0F : ((a)-(b))/(float)((c)-(b)))
#define CLAMP_TYPE(a, b, c) \
    (a) = (((a) < (b)) ? (b) : (((a) > (c)) ? (c) : (a)))
#define CLAMP_FORTYPE(a,b,c) \
    (((a) < (b)) ? (b) : (((a) > (c)) ? (c) : (a)))

/*
    The following type definitions shall be assumed to be vectors,
        but they may not be limited to only those functions. For
        example a float2 could be used as a two dimensional vector,
        though in other use-cases it could be a 1X2 or 2x1 matrix
        if no such type were to exist.
    Even though they can represent much more than plain vectors, 
        these variables do assume this use. So, by example, using
        "int3" as an RGB variable, you'd have to remember that the 
        "green channel" is ".y", and not ".g" which is undefined.
    
    Previously this math header/library utilised an OOP-style for 
        its buffers, where each buffer would contain its own 
        functions' pointers. This has been rewritten to a more memory-
        friendly approach, where currently the remaining overhead
        that remains are function calls. If this becomes a issue on
        RETRO_SYS platforms, another approach, likely using macros 
        can be taken.
*/

typedef struct float2 {
    float x, y;
} float2;
typedef struct float3 {
    float x, y, z;
} float3;
typedef struct float4 {
    float x,y,z,w;
} float4;

typedef struct int2 {
    int x,y;
} int2;
typedef struct int3 {
    int x,y,z;
} int3;
typedef struct int4 {
    int x,y,z,w;
} int4;

typedef struct buffer_float {
    float*data;
    size_t size;
} buffer_float;
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

typedef struct {
    const size_t index;
    buffer_float* storage;
} stored_float;
typedef struct {
    const size_t index;
    buffer_float2* storage;
} stored_float2;
typedef struct {
    const size_t index;
    buffer_float3* storage;
} stored_float3;
typedef struct {
    const size_t index;
    buffer_float4* storage;
} stored_float4;

void Normalize_Vector2(float2*);
void Normalize_Vector3(float3*);
void Normalize_Vector4(float4*);

void Clamp_Int(int* var, const int min, const int max);
void Clamp_UInt(size_t *var, const size_t min, const size_t max);
void Clamp_Float(float*var, const float min, const float max);
int ClampI_Int(const int var, const int min, const int max);
size_t ClampU_UInt(const size_t var, const size_t min, const size_t max);
int ClampI_Float(const float var, const float min, const float max);
float ClampF_Int(const int var, const int min, const int max);
float ClampF_Float(const float var, const float min, const float max);
void Normalize_Float(float* var, const float min, const float max); //= macro with added div0 checks
float NormalizeF_Int(const int var, const int min, const int max); //= macro with added div0 checks
float NormalizeF_Float(const float var, const float min, const float max); //= macro with added div0 checks

buffer_float Create_FloatBuf(const size_t);
buffer_float2 Create_Float2Buf(const size_t); // always check your .data
buffer_float3 Create_Float3Buf(const size_t); // always check your .data
buffer_float4 Create_Float4Buf(const size_t); // always check your .data

void Set_Float(buffer_float*, const size_t, const float val); // If you need to pass '&', just use "[indx]" or the macro
void Set_Float2(buffer_float2*, const size_t, const float2 val);
void Set_Float3(buffer_float3*, const size_t, const float3 val);
void Set_Float4(buffer_float4*, const size_t, const float4 val);

void Add_Float2(float2*, float2*);
float2 AddF2_Float2(const float2, const float2);
void Add_Float2F(float2*, const float beta);
float2 AddF2_Float2F(const float2, const float beta);
void Add_Float3(float3*, float3*);
float3 AddF3_Float3(const float3, const float3);
void Add_Float3F(float3*, const float beta);
void Add_Float3F2(float3*, float2*, const size_t omit);

float Get_Float(buffer_float*, const size_t);
float2 Get_Float2(buffer_float2*, const size_t);
float3 Get_Float3(buffer_float3*, const size_t);
float4 Get_Float4(buffer_float4*, const size_t);

stored_float Store_Float(buffer_float*, const size_t, const float val);
stored_float2 Store_Float2(buffer_float2*, const size_t, const float2);
stored_float3 Store_Float3(buffer_float3*, const size_t, const float3);
stored_float4 Store_Float4(buffer_float4*, const size_t, const float4);

void Resize_FloatBuf(buffer_float*, const size_t);
void Resize_Float2Buf(buffer_float2*, const size_t);
void Resize_Float3Buf(buffer_float3*, const size_t);
void Resize_Float4Buf(buffer_float4*, const size_t);

void Edit_Float2(float2*, const float x, const float y);
void Edit_Float3(float3*, const float x, const float y, const float z);
void Edit_Float4(float4*, const float x, const float y, const float z, const float w);

void Free_Float2Buf(buffer_float2*);
void Free_Float3Buf(buffer_float3*);
void Free_Float4Buf(buffer_float4*);

float q_sqrt(float);

#endif