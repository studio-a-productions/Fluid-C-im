#include "cim_math.h"

float q_sqrt( float number )
{
    #if PLATFORM == RETRO_SYS
    /*
    ** This is the "fast inverse square root" method of quake,
    ** straigth from Wikipedia. The only change is that we've made it
    ** be the actual square root by returning the inverse.
    **
    ** Why we use this instead of the actual square root, well we might
    ** need it in the future so yeah.
    */

	long i;
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = number * 0.5F;
	y  = number;
	i  = * ( long * ) &y; 
	i  = 0x5f3759df - ( i >> 1 ); 
	y  = * ( float * ) &i;
	y  = y * ( threehalfs - ( x2 * y * y ) );   
//	y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

	return 1/y; // literally the only original thing ;-;
    #elif PLATFORM == MODERN_SYS
    /*
    ** For modern systems "rsqrtss" actually is faster, so if 
    ** we can implement/call it, that would be great!
    */
    return SDL_sqrt(number);
    #else
    #error cim_math.h: platform implementation not set for Cim_Math::q_sqrt(float) -type float!
    #endif
}

static inline void Normalize_Vector2(float2 *vec) {
    if (!vec->x && !vec->y)
    return;
    const float length = q_sqrt(ADD(SQUARE(vec->x), SQUARE(vec->y)));
    vec->x /= length;
    vec->y /= length;
}
void Normalize_Vector3(float3* vec) {
    if (!vec->x && !vec->y && !vec->z)
    return;
    const float length = q_sqrt(ADD3(SQUARE(vec->x), SQUARE(vec->y), 
        SQUARE(vec->z)));
    vec->x /= length;
    vec->y /= length;
    vec->z /= length;
}
void Normalize_Vector4(float4 *vec) {
    if (!vec->x && !vec->y && !vec->z && !vec->w)
    return;
    const float length = q_sqrt(ADD(ADD(SQUARE(vec->x), SQUARE(vec->y)), 
        ADD(SQUARE(vec->z), SQUARE(vec->w))));
    vec->x /= length;
    vec->y /= length;
    vec->z /= length;
    vec->w /= length;
}

void Clamp_Int(int* var, const int min, const int max) {
    if (min < max)
        if (*var > max) *var = max;
        else if (*var < min) *var = min;
}
void Clamp_UInt(size_t*var, const size_t min, const size_t max) {
    if (min < max)
        if (*var > max) *var = max;
        else if (*var < min) *var = min;
}
void Clamp_Float(float* var, const float min, const float max) {
    if (min < max)
        if (*var > max) *var = max;
        else if (*var < min) *var = min;
}
int ClampI_Int(const int var, const int min, const int max) {
    return (var < min ? min : (var > max ? max : var));
}
size_t ClampU_UInt(const size_t var, const size_t min, const size_t max) {
    return (var < min ? min : (var > max ? max : var));
}
int ClampI_Float(const float var, const float min, const float max) {
    return (int)(var < min ? min : (var > max ? max : var));
}
float ClampF_Int(const int var, const int min, const int max) {
    return (float)(var < min ? min : (var > max ? max : var));
}
float ClampF_Float(const float var, const float min, const float max) {
    return (var < min ? min : (var > max ? max : var));
}
void Normalize_Float(float*var, const float min, const float max) {
    if (max-min) NORMALIZE_TYPE(*var, min, max);
}
float NormalizeF_Int(const int var, const int min, const int max) {
    if (max-min) return NORMALIZE_FORTYPE(var, min, max);
    else return (float)var;
}
float NormalizeF_Float(const float var, const float min, const float max) {
    if (max-min) return NORMALIZE_FORTYPE(var, min, max);
    else return var;
}

void Resize_FloatBuf(buffer_float* buff, const size_t s_n) {
    float*buff_n = SDL_realloc(buff->data, s_n);
    if (buff_n) { buff->data = buff_n; buff->size = s_n; }
}
void Resize_Float2Buf(buffer_float2* buffer, const size_t new_size) {
    const size_t alloc_size = MULT(new_size*sizeof(float), 2);
    float *new_buffer = SDL_realloc(buffer->data, alloc_size);
    if (new_buffer) { buffer->data = new_buffer; buffer->size = new_size; }
}
void Resize_Float3Buf(buffer_float3* buffer, const size_t new_size) {
    const size_t alloc_size = new_size*sizeof(float)*3;
    float *new_buffer = SDL_realloc(buffer->data, alloc_size);
    if (new_buffer) { buffer->data = new_buffer; buffer->size = new_size; }
}
void Resize_Float4Buf(buffer_float4* buff, const size_t n_size) {
    const size_t alloc_s = n_size*sizeof(float)*4;
    float *n_buff = SDL_realloc(buff->data, alloc_s);
    if (n_buff) { buff->data = n_buff; buff->size = n_size; }
}

void Set_Float(buffer_float* buff, const size_t indx, const float val) {
    buff->data[indx] = val;
}
void Set_Float2(buffer_float2*buff, const size_t indx, const float2 val) {
    buff->data[MULT(indx, 2)] = val.x;
    buff->data[ADD(MULT(indx, 2), 1)] = val.y;
}
void Set_Float3(buffer_float3*buff, const size_t indx, const float3 val) {
    buff->data[MULT(indx, 3)] = val.x;
    buff->data[ADD(MULT(indx, 3), 1)] = val.y;
    buff->data[ADD(MULT(indx, 3), 2)] = val.z;
}
void Set_Float4(buffer_float4*buff, const size_t indx, const float4 val) {
    buff->data[MULT(indx, 4)] = val.x;
    buff->data[ADD(MULT(indx, 4), 1)] = val.y;
    buff->data[ADD(MULT(indx, 4), 2)] = val.z;
    buff->data[ADD(MULT(indx, 4), 3)] = val.w;
}

void Add_Float2(float2* alpha, float2* beta) {
    alpha->x += beta->x;
    alpha->y += beta->y;
}
float2 AddF2_Float2(const float2 alpha, const float2 beta) {
    const float2 gamma = {
        alpha.x + beta.x,
        alpha.y + beta.y
    };
    return gamma;
}
void Add_Float2F(float2* alpha, const float beta) {
    alpha->x += beta;
    alpha->y += beta;
}
float2 AddF2_Float2F(const float2 alpha, const float beta) {
    const float2 gamma = {
        alpha.x+beta,
        alpha.y+beta
    };
    return gamma;
}
void Add_Float3(float3* alpha, float3* beta) {
    alpha->x += beta->x;
    alpha->y += beta->y;
    alpha->z += beta->z;
}
float3 AddF3_Float3(const float3 alpha, const float3 beta) {
    const float3 gamma = {
        alpha.x + beta.x,
        alpha.y + beta.y,
        alpha.z + beta.z
    };
    return gamma;
}
void Add_Float3F(float3* alpha, const float beta) {
    alpha->x += beta;
    alpha->y += beta;
    alpha->z += beta;
}
void Add_Float3F2(float3*alpha, float2*beta, const size_t omit) {
    
}

float Get_Float(buffer_float* buff, const size_t indx) {
    return buff->data[indx];
}
float2 Get_Float2(buffer_float2 *buffer, const size_t i) {
    float2 c_data = { buffer->data[MULT(i,2)], buffer->data[ADD(MULT(i, 2), 1)] };
    return c_data;
}
float3 Get_Float3(buffer_float3 *buffer, const size_t i) {
    float3 c_data = { 
        buffer->data[MULT(i,3)], 
        buffer->data[ADD(MULT(i, 3), 1)],
        buffer->data[ADD(MULT(i, 3), 2)]
    };
    return c_data;
}
float4 Get_Float4(buffer_float4 *buff, const size_t indx) {
    float4 c = {
        buff->data[MULT(indx, 4)],
        buff->data[ADD(MULT(indx, 4), 1)],
        buff->data[ADD(MULT(indx, 4), 2)],
        buff->data[ADD(MULT(indx, 4), 3)],
    };
    return c;
}

stored_float Store_Float(buffer_float* buff, const size_t indx, const float var) {
    buff->data[indx] = var;
    stored_float data_p = { indx, buff };
    return data_p;
}
stored_float2 Store_Float2(buffer_float2* buff, const size_t indx, const float2 var) {
    buff->data[MULT(indx, 2)] = var.x;
    buff->data[ADD(MULT(indx, 2), 1)] = var.y;
    stored_float2 data_p = { indx, buff };
    return data_p;
}
stored_float3 Store_Float3(buffer_float3* buff, const size_t indx, const float3 var) {
    buff->data[MULT(indx, 3)] = var.x;
    buff->data[ADD(MULT(indx, 3), 1)] = var.y;
    buff->data[ADD(MULT(indx, 3), 2)] = var.z;
    stored_float3 data_p = { indx, buff };
    return data_p;
}
stored_float4 Store_Float4(buffer_float4* buff, const size_t indx, const float4 var) {
    buff->data[MULT(indx, 4)] = var.x;
    buff->data[ADD(MULT(indx, 4), 1)] = var.y;
    buff->data[ADD(MULT(indx, 4), 2)] = var.z;
    buff->data[ADD(MULT(indx, 4), 3)] = var.w;
    stored_float4 data_p = { indx, buff };
    return data_p;
}
buffer_float Create_FloatBuf(const size_t memb) {
    const buffer_float buff = {
        .data = SDL_malloc(memb*sizeof(float)),
        .size = memb
    };
    return buff;
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

void Edit_Float2(float2 *var, const float xvar, const float yvar) {
    var->x = xvar;
    var->y = yvar;
}
void Edit_Float3(float3 *var, const float xvar, const float yvar, const float zvar) {
    var->x = xvar;
    var->y = yvar;
    var->z = zvar;
}
void Edit_Float4(float4 *var, const float xvar, const float yvar, const float zvar, const float wvar) {
    var->x = xvar;
    var->y = yvar;
    var->z = zvar;
    var->w = wvar;
}

void Free_FloatBuf(buffer_float* buffer) {
    SDL_free(buffer->data);
    buffer->size = 0;
}
void Free_Float2Buf(buffer_float2 *buffer) {
    SDL_free(buffer->data);
    buffer->size = 0;
}
void Free_Float3Buf(buffer_float3 *buffer) {
    SDL_free(buffer->data);
    buffer->size = 0;
}
void Free_Float4Buf(buffer_float4* buffer) {
    SDL_free(buffer->data);
    buffer->size = 0;
}