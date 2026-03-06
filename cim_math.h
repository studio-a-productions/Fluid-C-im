#ifndef CIM_MATH_H
#define CIM_MATH_H

#include <stdio.h>
#include <SDL.h>
#include "cim_environment.h"


/*
    Functions declared may be unsafe, always check the result.
*/


#define ADD(a, b) ((a)+(b))
#define ADD3(a, b, c) ((a) + (b) + (c))
#define SUB(a, b) ((a)-(b))
#define MULT(a, b) ((a)*(b))
#define DIV(a, b) ((a)/(b))
#define SQUARE(a) ((a)*(a))


// --- float_  operations ---
// ++  buffer_float_ oppr  ++ 
// SET_FLOAT* IS ONLY INITIAL

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

#define CLAMPVEC2_TYPE(a, b, c) \
    do { \
        \
    } while (0)

#define CASTVEC2_TYPE(a, b, c) \
    do { \
        (a).x = (b)((c).x); \
        (a).y = (b)((c).y); \
    } while (0)
#define CASTVEC3_TYPE(a,b,c) \
    do { \
        (a).x = (b)((c).x); \
        (a).y = (b)((c).y); \
        (a).z = (b)((c).z); \
    } while (0)
#define CASTVEC4_TYPE(a,b,c) \
    do { \
        (a).x = (b)((c).x); \
        (a).y = (b)((c).y); \
        (a).z = (b)((c).z); \
        (a).w = (b)((c).w); \
    } while (0)

// these are for init only 

#define CASTVEC2_FORTYPE(a, b) \
    { \
        (a)((b).x), \
        (a)((b).y) \
    }
#define CASTVEC3_FORTYPE(a, b) \
    { \
        (a)((b).x), \
        (a)((b).y), \
        (a)((b).z) \
    }
#define CASTVEC4_FORTYPE(a, b) \
    { \
        (a)((b).x), \
        (a)((b).y), \
        (a)((b).z), \
        (a)((b).w) \
    }

#define EQUALIZEVEC2_TYPE(a, b) \
    do { \
        (a).x = (b); \
        (a).y = (b); \
    } while(0)
#define EQUALIZEVEC3_TYPE(a, b) \
    do { \
        (a).x = (b); \
        (a).y = (b); \
        (a).z = (b); \
    } while(0)
#define EQUALIZEVEC4_TYPE(a, b) \
    do { \
        (a).x = (b); \
        (a).y = (b); \
        (a).z = (b); \
        (a).w = (b); \
    } while(0)

#define CLAMPVEC2_TYPE(a, b, c) \
    do { \
        CLAMP_TYPE((a).x, (b).x, (c).x); \
        CLAMP_TYPE((a).y, (b).y, (c).y); \
    } while(0) 
#define CLAMPVEC3_TYPE(a,b,c) \
    do { \
        CLAMP_TYPE((a).x, (b).x, (c).x); \
        CLAMP_TYPE((a).y, (b).y, (c).y); \
        CLAMP_TYPE((a).z, (b).z, (c).z); \
    } while(0) 
#define CLAMPVEC4_TYPE(a,b,c) \
    do { \
        CLAMP_TYPE((a).x, (b).x, (c).x); \
        CLAMP_TYPE((a).y, (b).y, (c).y); \
        CLAMP_TYPE((a).z, (b).z, (c).z); \
        CLAMP_TYPE((a).w, (b).w, (c).w); \
    } while(0) 

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
    It's recommended to use the marcos declared above for optimization 
        purposes, both for application and ease of use. While anyone 
        using an IDE or code editor like VSC might be able to see
        variables and functions after typing one or two characters, it
        would still give you a large list you'd need to parse for your
        specific use case, and thus (unless you are re-assigning) you
        should use the macros instead. You need not concern yourself
        with type conversion when using these.
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
    int32_t x,y;
} int2;
typedef struct int2_t8 {
    int8_t x,y;
} int2_t8;
typedef struct int2_t16 {
    int16_t x,y;
} int2_t16;
typedef struct int3 {
    int32_t x,y,z;
} int3;
typedef struct int3_t8 {
    int8_t x,y,z;
} int3_t8;
typedef struct int3_t16 {
    int16_t x,y,z;
} int3_t16;
typedef struct int4 {
    int32_t x,y,z,w;
} int4;
typedef struct int4_t8 {
    int8_t x,y,z,w;
} int4_t8;
typedef struct int4_t16 {
    int16_t x,y,z,w;
} int4_t16;


typedef struct uint2 {
    uint32_t x, y;
} uint2;
typedef struct uint2_t8 {
    uint8_t x, y;
} uint2_t8;
typedef struct uint2_t16 {
    uint16_t x, y;
} uint2_t16;
typedef struct uint3 {
    uint32_t x, y, z;
} uint3;
typedef struct uint3_t8 {
    uint8_t x, y, z;
} uint3_t8;
typedef struct uint3_t16 {
    uint16_t x, y, z;
} uint3_t16;
typedef struct uint4 {
    uint32_t x, y, z, w;
} uint4;
typedef struct uint4_t8 {
    uint8_t x, y, z, w;
} uint4_t8;
typedef struct uint4_t16 {
    uint16_t x, y, z, w;
} uint4_t16;

void Normalize_Vector2(float2*);
void Normalize_Vector3(float3*);
void Normalize_Vector4(float4*);

void Clamp_Int(int*const var, const int min, const int max);
void Clamp_UInt(size_t*const var, const size_t min, const size_t max);
void Clamp_Float(float*const var, const float min, const float max);
int ClampI_Int(const int var, const int min, const int max);
size_t ClampU_UInt(const size_t var, const size_t min, const size_t max);
int ClampI_Float(const float var, const float min, const float max);
float ClampF_Int(const int var, const int min, const int max);
float ClampF_Float(const float var, const float min, const float max);

// will be abandoned for favor of CLAMPVEC_TYPE
/*
void Clamp_Int2(int2*const var, const int2 min, const int2 max);
void Clamp_Int2t8(int2_t8*const var, const int2_t8 min, const int2_t8 max);
void Clamp_Int2t16(int2_t16*const var, const int2_t16 min, const int2_t16 max);
void Clamp_Int2I(int2*const var, const int min, const int max);
void Clamp_Int2t8I(int2_t8*const var, const int min, const int max);
void Clamp_Int2t16I(int2_t16*const var, const int min, const int max);
void Clamp_Int3(int3*const var, const int3 min, const int2 max);
void Clamp_Int3t8(int3_t8*const var, const int3_t8 min, const int3_t8 max);
void Clamp_Int3t16(int3_t16*const var, const int3_t16 min, const int3_t16 max);
void Clamp_Int4(int4*const var, const int4 min, const int4 max);
void Clamp_Int4t8(int4_t8*const var, const int4_t8 min, const int4_t8);
void Clamp_Int4t16(int4_t16*const var, const int4_t16 min, const int4_t16 max);
*/

void Normalize_Float(float* var, const float min, const float max); //= macro with added div0 checks
float NormalizeF_Int(const int var, const int min, const int max); //= macro with added div0 checks
float NormalizeF_Float(const float var, const float min, const float max); //= macro with added div0 checks


void Add_Float2(float2* const alpha, const float2* beta);
float2 AddF2_Float2(const float2, const float2);
void Add_Float2F(float2* const alpha, const float beta);
float2 AddF2_Float2F(const float2, const float beta);
void Add_Float3(float3 *const alpha, const float3* beta);
float3 AddF3_Float3(const float3, const float3);
void Add_Float3F(float3* const alpha, const float beta);
float3 AddF3_Float3F(const float3, const float beta);
void Add_Float3F2(float3* const alpha, const float2* beta, const uint8_t omit);

void Edit_Float2(float2*const var, const float x, const float y);
void Edit_Float3(float3*const var, const float x, const float y, const float z);
void Edit_Float4(float4*const var, const float x, const float y, const float z, const float w);

float q_sqrt(float);

#endif