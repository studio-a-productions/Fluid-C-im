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

void Clamp_Int(int*const var, const int min, const int max) {
    if (min < max)
        if (*var > max) *var = max;
        else if (*var < min) *var = min;
}
void Clamp_UInt(size_t*var, const size_t min, const size_t max) {
    if (min < max)
        if (*var > max) *var = max;
        else if (*var < min) *var = min;
}
void Clamp_Float(float*const var, const float min, const float max) {
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

void Add_Float2(float2* const alpha, const float2* beta) {
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
void Add_Float2F(float2* const alpha, const float beta) {
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
void Add_Float3(float3* const alpha, const float3* beta) {
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
void Add_Float3F(float3* const alpha, const float beta) {
    alpha->x += beta;
    alpha->y += beta;
    alpha->z += beta;
}
float3 AddF3_Float3F(const float3 alpha, const float beta) {
    const float3 gamma={
        alpha.x+beta,
        alpha.y+beta,
        alpha.z+beta
    };
    return gamma;
}
void Add_Float3F2(float3* const alpha, const float2* beta, const uint8_t omit) {
    /* Old "slower" approach (slower would be if statements)
    alpha->x += omit  ? beta->x : 0.0F;
    alpha->y += !omit ? beta->x : omit==2 ? beta->y : 0.0F;
    alpha->z += !omit ? beta->y : omit==1 ? beta->x : 0.0F; 

    When we write firmware, we should expose a simple-ish library
        for single bit or '< byte' types. A custom memory controller,
        which would probably be needed, might be able to actually pack
        data closer together than modern systems allow, which means we
        could have a more "packed" memory layout and more space for 
        more useful stuff.
    
    */
    switch (omit) {
        case 0:
            alpha->y += beta->x;
            alpha->z += beta->y;
            break;
        case 1:
            alpha->x += beta->x;
            alpha->z += beta->y;
            break;
        case 2: 
            alpha->x += beta->x;
            alpha->y += beta->y;
            break;
        default:
            break;
    }
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
