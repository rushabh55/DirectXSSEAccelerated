#pragma once

// STL includes

#include <math.h> 

#ifdef _FINAL 
#ifndef INLINE 
#define INLINE __forceinline
#endif
#elif _DEMO1
#ifndef INLINE
#define INLINE 
#endif
#else
#ifndef INLINE
#define INLINE
#endif
#endif

#ifndef SafeNuke
#define SafeNuke(p)       { if (p) { delete (p);     (p) = nullptr; } }
#endif
#ifndef ReleaseMacroArray
#define ReleaseMacroArray(p) { if (p) { delete[] (p);   (p) = nullptr; } }
#endif
#ifndef ReleaseMacro
#define ReleaseMacro(p)      { if (p) { (p)->Release(); (p) = nullptr; } }
#endif

#ifndef D3DCOLOR_ARGB
#define D3DCOLOR_ARGB(a,r,g,b) \
    ((DWORD)((((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff)))
#endif

#ifndef ASSERT
#define ASSERT( x ) { if ( !x ) throw 1; }
#endif
#ifndef ASSERTMSG
#define ASSERTMSG( x , y ) { if ( !x ) throw y; }
#endif

typedef char i8;
typedef short i16;
typedef int i32;
typedef long long i64;

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

#if defined( _WIN64 )
typedef u64 uptr;
#else
/*typedef W64SAFE u32 uptr;*/
#endif

typedef float f32;
typedef double f64;

typedef u8 Bool;     // Defines: True and False
typedef void* Handle;
typedef u32 Error;

typedef u32 Id;      // Local id, GUIDs are too slow and unnecessary for our purposes.

typedef char* pstr;
typedef const char* pcstr;

typedef void(*Callback)(void* pUserData);


#define MIN(x,y) ( ( (x) < (y) ) ? (x) : (y) )
#define MAX(x,y) ( ( (x) > (y) ) ? (x) : (y) )

namespace Math
{
	////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	///   Provides some functionality for dealing with angles.
	/// </summary>
	////////////////////////////////////////////////////////////////////////////////////////////////

	class Angle
	{
	public:

		static float Deg2Rad(f32 Degrees)
		{
			return Degrees * (Pi / 180.0f);
		}

		static f32 Sin(f32 Rad)
		{
			return sin(Rad);
		}

		static f32 Cos(f32 Rad)
		{
			return cos(Rad);
		}

		static f32 Tan(f32 Rad)
		{
			return tan(Rad);
		}

		static f32 ASin(f32 Rad)
		{
			return asin(Rad);
		}

		static f32 ACos(f32 Rad)
		{
			return acos(Rad);
		}

		static f32 ATan(f32 Rad)
		{
			return atan(Rad);
		}


	public:

		static const f32 Pi;
	};



	// Copyright © 2008 Intel Corporation
	// All Rights Reserved
	// 
	// The sample source code contained or described herein and all documents
	// related to the sample source code ("Material") are owned by Intel Corporation
	// or its suppliers or licensors. Title to the Material remains with Intel Corporation
	// or its suppliers and licensors. The Material may contain trade secrets and
	// proprietary and confidential information of Intel Corporation and its suppliers
	// and licensors, and is protected by worldwide copyright and trade secret laws and
	// treaty provisions. The sample source code is provided AS IS, with no warranties
	// of any kind, express or implied. Except as expressly permitted by the Software
	// license, neither Intel Corporation nor its suppliers assumes any responsibility
	// or liability for any errors or inaccuracies that may appear herein.
	
}