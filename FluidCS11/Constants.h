#pragma once
#include <intrin.h>
#include "Macros.h"
#include "DXUT.h"
#include "DXUTsettingsDlg.h"
#include "SDKmisc.h"
#include "resource.h"
#include "WaitDlg.h"
#include <sstream> 
#include <algorithm>

using namespace DirectX;
using namespace std;
#define _FINAL 1
#define NEW !_NEW

INLINE __m128 Add(__m128 a, __m128 b) 
{
	return _mm_add_ps(a, b);
}

INLINE __m128 Mult(const __m128& a, const float& scalar)
{
	const __m128& scalarA = _mm_set1_ps(scalar);
	return _mm_mul_ps(a, scalarA);
}

INLINE __m128 lerpAligned(const __m128& a, const __m128& b, const float& scalar)
{
	return Mult(Add(a, b), scalar);
}



INLINE f32 GetX( __m128 v )
{
	return v.m128_f32[0];
}

/// <summary>
///   Returns the y value of the vector.
/// </summary>
/// <returns>The y value of the vector.</returns>
INLINE f32 GetY( __m128 v )
{
	return v.m128_f32[1];
}

/// <summary>
///   Returns the z value of the vector.
/// </summary>
/// <returns>The z value of the vector.</returns>
INLINE f32 GetZ( const __m128& v )
{
	return v.m128_f32[2];
}

/// <summary>
///   Returns the y value of the vector.
/// </summary>
/// <returns>The w value of the vector.</returns>
INLINE f32 GetW( const __m128& v)
{
	return v.m128_f32[3];
}

INLINE __m128 CAST(	f32 x,	f32 y,	f32 z,	f32 w )
{
	return _mm_setr_ps(x,y,z,w);
}



/// <summary>
///   Convenience function for adding 3 __m128 types.
/// </summary>
/// <param name="a">The first variable to add.</param>
/// <param name="b">The second variable to add.</param>
/// <param name="c">The third variable to add.</param>
/// <returns>The three way add result.</returns>
__m128 INLINE _mm_add3_ps_composite(const __m128& a, const __m128& b, const __m128& c)
{
	return _mm_add_ps(_mm_add_ps(a, b), c);
}


/// <summary>
///   Convenience function for adding 4 __m128 types.
/// </summary>
/// <param name="a">The first variable to add.</param>
/// <param name="b">The second variable to add.</param>
/// <param name="c">The third variable to add.</param>
/// <param name="d">The fourth variable to add.</param>
/// <returns>The four way add result.</returns>
__m128 INLINE _mm_add4_ps_composite(const __m128& a, const __m128& b,
	const __m128& c, const __m128& d)
{
	return _mm_add_ps(_mm_add_ps(a, b), _mm_add_ps(c, d));
}


/// <summary>
///   Divides 2 __m128 types and zeroes out indeterminate values caused by divide-by-zero.
/// </summary>
/// <remarks>This function is used when masking divide-by-zero.</remarks>
/// <param name="a">The dividend.</param>
/// <param name="b">The divisor.</param>
/// <returns>The quotient.</returns>
__m128 INLINE _mm_div_ps_composite(const __m128& a, const __m128& b)
{
	__m128 xMask = _mm_cmpneq_ps(b, _mm_setzero_ps());
	__m128 t = _mm_div_ps(a, b);
	t = _mm_and_ps(t, xMask);
	return t;
}


#ifndef NEW 
__delcspec(align(16)) typedef struct Particle
{
	XMFLOAT2 vPosition;
	XMFLOAT2 vVelocity;
};

#endif
#ifdef NEW
__declspec(align(16))
struct Particle
{
	XMVECTOR VARS;
};
#endif
struct ParticleDensity
{
	f32 fDensity;
};

 typedef struct ParticleForces
{
	XMFLOAT2 vAcceleration;


};

struct u322
{
	u32 x;
	u32 y;
} __declspec(align(16));


typedef struct FOO
{
#ifdef _FINAL
	__declspec(align(16)) __m128 foo;
#endif
#ifndef _FINAL
	XMFLOAT4 foo;
#endif
	~FOO(){
		//delete foo;
	}
}__declspec(align(16));
//--------------------------------------------------------------------------------------
// Global variables
//--------------------------------------------------------------------------------------

// Compute Shader Constants
// Grid cell key size for sorting, 8-bits for x and y
const u64 NUM_GRID_INDICES = 65536;

// Numthreads size for the simulation
const u32 SIMULATION_BLOCK_SIZE = 256;

// Numthreads size for the sort
const u32 BITONIC_BLOCK_SIZE = 256;
const u32 TRANSPOSE_BLOCK_SIZE = 16;

// For this sample, only use power-of-2 numbers >= 8K and <= 64K
// The algorithm can be extended to support any number of particles
// But to keep the sample simple, we do not implement boundary conditions to handle it
const u32 NUM_PARTICLES_64K = 16 * 1024;
u32 g_iNumParticles = NUM_PARTICLES_64K;

// Particle Properties
// These will control how the fluid behaves



static const f32 g_fInitialParticleSpacing = 0.0045f;
static const f32 g_fSmoothlen = .012f;
static const f32 g_fPressureStiffness = 4096;
static const u64 g_fRestDensity = 4096;
const f32 g_fParticleMass = 0.0002f;
const f32 g_fViscosity = 4.1f;
const f32 g_fMaxAllowableTimeStep = 0.05f;
const f32 g_fParticleRenderSize = 0.00501f;


// Gravity Directions
static const XMFLOAT2A GRAVITY_DOWN(0, -1.0f);
XMFLOAT2A g_vGravity = GRAVITY_DOWN;

// Map Size
// These values should not be larger than 256 * fSmoothlen
// Since the map must be divided up into fSmoothlen sized grid cells
// And the grid cell is used as a 16-bit sort key, 8-bits for x and y
static const f32 g_fMapHeight = 1.2f;
static const f32 g_fMapWidth = (4.0f / 3.0f) * g_fMapHeight;

// Map Wall Collision Planes
static const f32 g_fWallStiffness = 300000.0f;
static const XMFLOAT3A g_vPlanes[4] = {
	XMFLOAT3A(1, 0, 0),
	XMFLOAT3A(0, 1, 0),
	XMFLOAT3A(-1, 0, g_fMapWidth),
	XMFLOAT3A(0, -1, g_fMapHeight)
};

// Simulation Algorithm
enum eSimulationMode
{
	SIM_MODE_SIMPLE,
	SIM_MODE_SHARED,
	SIM_MODE_GRID
};

eSimulationMode g_eSimMode = SIM_MODE_GRID;
