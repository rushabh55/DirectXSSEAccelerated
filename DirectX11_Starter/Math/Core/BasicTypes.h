#pragma once 
#include <intrin.h>

typedef char i8;
typedef unsigned char u8;
typedef short i16;
typedef unsigned short u16;
typedef int i32;
typedef unsigned int u32;
typedef long long i64;
typedef unsigned long long u64;

typedef float f32;
typedef double f64;

typedef char Bool;

#if defined ( _WIN64 )
typedef u64 uptr;
#else
typedef u32* uptr;
#endif

typedef void* Handle;
typedef u64 Error;

typedef u32 Id;

typedef char* pstr;
typedef const char* pcstr;

typedef void(*Callback)(void * fPtr);

typedef __m128 i128;

__m128 __forceinline _mm_add3_ps_composite(const __m128& a, const __m128& b, const __m128& c)
{
	return _mm_add_ps(_mm_add_ps(a, b), c);
}