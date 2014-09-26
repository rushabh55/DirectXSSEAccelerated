#pragma once
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

struct Particle
{
	XMFLOAT2 vPosition;
	XMFLOAT2 vVelocity;
};

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

//--------------------------------------------------------------------------------------
// Global variables
//--------------------------------------------------------------------------------------

// Compute Shader Constants
// Grid cell key size for sorting, 8-bits for x and y
const u64 NUM_GRID_INDICES = 65536;

// Numthreads size for the simulation
const u32 SIMULATION_BLOCK_SIZE = 256;

// Numthreads size for the sort
const u32 BITONIC_BLOCK_SIZE = 512;
const u32 TRANSPOSE_BLOCK_SIZE = 16;

// For this sample, only use power-of-2 numbers >= 8K and <= 64K
// The algorithm can be extended to support any number of particles
// But to keep the sample simple, we do not implement boundary conditions to handle it
const u32 NUM_PARTICLES_64K = 64 * 1024;
u32 g_iNumParticles = NUM_PARTICLES_64K;

// Particle Properties
// These will control how the fluid behaves



static const f32 g_fInitialParticleSpacing = 0.0045f;
static const f32 g_fSmoothlen = .012f;
static const f32 g_fPressureStiffness = 2000.0f;
static const u64 g_fRestDensity = 4096;
const f32 g_fParticleMass = 0.0002f;
const f32 g_fViscosity = 5.1f;
const f32 g_fMaxAllowableTimeStep = 0.05f;
const f32 g_fParticleRenderSize = 0.01f;


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
static const f32 g_fWallStiffness = 30000.0f;
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
