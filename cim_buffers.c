#include <SDL.h>
#include "cim_buffers.h"

buffer_string Create_StringBuf(const size_t s) {
    buffer_string buff = {
        .data = SDL_calloc(s, sizeof(char*)),
        .size = s
    };
    return buff;
}
stored_string Store_String(buffer_string*const buff, const size_t indx, const char* stringy) {
    buff->data[indx] = SDL_strdup(stringy);
    stored_string data_p = { indx, buff };
    return data_p;
}
char *Get_String(buffer_string*const buff, const size_t indx) {
    return buff->data[indx];
}
void Set_String(buffer_string *const buff, const size_t indx, const char* stringy) {
    SDL_free(buff->data[indx]);
    buff->data[indx] = SDL_strdup(stringy);
}
void Resize_StringBuf(buffer_string*const buff, const size_t size_n) {
    char** tmp = SDL_realloc(buff->data, sizeof(char*)*size_n);
    if (tmp) { buff->data = tmp; buff->size = size_n; }
}
void Free_StringBuf(buffer_string*const buff) {
    for (size_t i = 0; i < buff->size; i++) {
        SDL_free((void*)buff->data[i]);
    }
    SDL_free(buff->data);
    buff->data = NULL;
    buff->size = 0;
}


buffer_float Create_FloatBuf(const size_t memb) {
    const buffer_float buff = {
        .data = SDL_malloc(memb*sizeof(float)),
        .size = memb
    };
    return buff;
}
stored_float Store_Float(buffer_float*const buff, const size_t indx, const float var) {
    buff->data[indx] = var;
    stored_float data_p = { indx, buff };
    return data_p;
}
float Get_Float(buffer_float*const buff, const size_t indx) {
    return buff->data[indx];
}
void Set_Float(buffer_float*const buff, const size_t indx, const float val) {
    buff->data[indx] = val;
}
void Resize_FloatBuf(buffer_float*const buff, const size_t s_n) {
    float*buff_n = SDL_realloc(buff->data, s_n*sizeof(float));
    if (buff_n) { buff->data = buff_n; buff->size = s_n; }
}
void Free_FloatBuf(buffer_float*const buffer) {
    SDL_free(buffer->data);
    buffer->data = NULL;
    buffer->size = 0;
}

buffer_uintt8 Create_UIntt8Buf(const size_t memb) {
    const buffer_uintt8 buff = {
        .data = SDL_malloc(memb*sizeof(uint8_t)),
        .size = memb
    };
    return buff;
}
stored_uintt8 Store_UIntt8(buffer_uintt8*const buff, const size_t indx, const uint8_t var) {
    buff->data[indx] = var;
    stored_uintt8 data_p = { indx, buff };
    return data_p;
}
uint8_t Get_UIntt8(buffer_uintt8*const buff, const size_t indx) {
    return buff->data[indx];
}
void Set_UIntt8(buffer_uintt8*const buff, const size_t indx, const uint8_t val) {
    buff->data[indx] = val;
}
void Resize_UIntt8Buf(buffer_uintt8*const buff, const size_t s_n) {
    uint8_t*buff_n = SDL_realloc(buff->data, s_n*sizeof(uint8_t));
    if (buff_n) { buff->data = buff_n; buff->size = s_n; }
}
void Free_UIntt8Buf(buffer_uintt8*const buffer) {
    SDL_free(buffer->data);
    buffer->data = NULL;
    buffer->size = 0;
}

#ifdef CIM_MATH_H


void Resize_Float2Buf(buffer_float2*const buffer, const size_t new_size) {
    const size_t alloc_size = MULT(new_size*sizeof(float), 2);
    float *new_buffer = SDL_realloc(buffer->data, alloc_size);
    if (new_buffer) { buffer->data = new_buffer; buffer->size = new_size; }
}
void Resize_Float3Buf(buffer_float3*const buffer, const size_t new_size) {
    const size_t alloc_size = new_size*sizeof(float)*3;
    float *new_buffer = SDL_realloc(buffer->data, alloc_size);
    if (new_buffer) { buffer->data = new_buffer; buffer->size = new_size; }
}
void Resize_Float4Buf(buffer_float4*const buff, const size_t n_size) {
    const size_t alloc_s = n_size*sizeof(float)*4;
    float *n_buff = SDL_realloc(buff->data, alloc_s);
    if (n_buff) { buff->data = n_buff; buff->size = n_size; }
}

void Set_Float2(buffer_float2*const buff, const size_t indx, const float2 val) {
    buff->data[MULT(indx, 2)] = val.x;
    buff->data[ADD(MULT(indx, 2), 1)] = val.y;
}
void Set_Float3(buffer_float3*const buff, const size_t indx, const float3 val) {
    buff->data[MULT(indx, 3)] = val.x;
    buff->data[ADD(MULT(indx, 3), 1)] = val.y;
    buff->data[ADD(MULT(indx, 3), 2)] = val.z;
}
void Set_Float4(buffer_float4*const buff, const size_t indx, const float4 val) {
    buff->data[MULT(indx, 4)] = val.x;
    buff->data[ADD(MULT(indx, 4), 1)] = val.y;
    buff->data[ADD(MULT(indx, 4), 2)] = val.z;
    buff->data[ADD(MULT(indx, 4), 3)] = val.w;
}

float2 Get_Float2(buffer_float2*const buffer, const size_t i) {
    float2 c_data = { buffer->data[MULT(i,2)], buffer->data[ADD(MULT(i, 2), 1)] };
    return c_data;
}
float3 Get_Float3(buffer_float3 *const buffer, const size_t i) {
    float3 c_data = { 
        buffer->data[MULT(i,3)], 
        buffer->data[ADD(MULT(i, 3), 1)],
        buffer->data[ADD(MULT(i, 3), 2)]
    };
    return c_data;
}
float4 Get_Float4(buffer_float4*const buff, const size_t indx) {
    float4 c = {
        buff->data[MULT(indx, 4)],
        buff->data[ADD(MULT(indx, 4), 1)],
        buff->data[ADD(MULT(indx, 4), 2)],
        buff->data[ADD(MULT(indx, 4), 3)],
    };
    return c;
}

float2 Deref_Float2(float*const p) {
    float2 var = {
        *p,
        p[1],
    };
    return var;
}
float3 Deref_Float3(float*const p) {
    float3 var = {
        *p,
        p[1],
        p[2],
    };
    return var;
}
float4 Deref_Float4(float*const p) {
    float4 var = {
        *p,
        p[1],
        p[2],
        p[3],
    };
    return var;
}

stored_float2 Store_Float2(buffer_float2*const buff, const size_t indx, const float2 var) {
    buff->data[MULT(indx, 2)] = var.x;
    buff->data[ADD(MULT(indx, 2), 1)] = var.y;
    stored_float2 data_p = { indx, buff };
    return data_p;
}
stored_float3 Store_Float3(buffer_float3*const buff, const size_t indx, const float3 var) {
    buff->data[MULT(indx, 3)] = var.x;
    buff->data[ADD(MULT(indx, 3), 1)] = var.y;
    buff->data[ADD(MULT(indx, 3), 2)] = var.z;
    stored_float3 data_p = { indx, buff };
    return data_p;
}
stored_float4 Store_Float4(buffer_float4*const buff, const size_t indx, const float4 var) {
    buff->data[MULT(indx, 4)] = var.x;
    buff->data[ADD(MULT(indx, 4), 1)] = var.y;
    buff->data[ADD(MULT(indx, 4), 2)] = var.z;
    buff->data[ADD(MULT(indx, 4), 3)] = var.w;
    stored_float4 data_p = { indx, buff };
    return data_p;
}

buffer_float2 Create_Float2Buf(const size_t members) {
    const size_t alloc_s = MULT(members*sizeof(float), 2);
    const buffer_float2 buffer = { 
        .data = SDL_malloc(alloc_s), 
        .size = members
    };
    return buffer;
}
buffer_float3 Create_Float3Buf(const size_t members) {
    const size_t alloc_s = MULT(members*sizeof(float), 3);
    const buffer_float3 buffer = { 
        .data = SDL_malloc(alloc_s), 
        .size = members
    };
    return buffer;
}
buffer_float4 Create_Float4Buf(const size_t memb) {
    const size_t alloc_s = memb * sizeof(float) * 4;
    const buffer_float4 buff = {
        .data = SDL_malloc(alloc_s),
        .size = memb
    };
    return buff;
}

void Free_Float2Buf(buffer_float2*const buffer) {
    SDL_free(buffer->data);
    buffer->data = NULL;
    buffer->size = 0;
}
void Free_Float3Buf(buffer_float3 *const buffer) {
    SDL_free(buffer->data);
    buffer->data = NULL;
    buffer->size = 0;
}
void Free_Float4Buf(buffer_float4*const buffer) {
    SDL_free(buffer->data);
    buffer->data = NULL;
    buffer->size = 0;
}

#endif