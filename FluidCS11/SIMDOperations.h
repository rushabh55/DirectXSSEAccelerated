#pragma once
#include "Macros.h"
#include "Constants.h"
#include <DirectXMath.h>
#include <vector>

using namespace std;
static vector<Particle> ParticlesRW;
static INLINE void Process(const unsigned int DTid, const XMFLOAT2 g_fTimeStep, vector<Particle> ParticlesRO,ParticleForces ParticlesForcesRO[])
{
	
	const unsigned int P_ID = DTid; // Particle ID to operate on

	XMFLOAT2 position = ParticlesRO.at(P_ID).vPosition;
	XMFLOAT2 velocity = ParticlesRO[P_ID].vVelocity;
	XMFLOAT2 acceleration = ParticlesForcesRO[P_ID].vAcceleration;


	for (unsigned int i = 0; i < 4; i++)
	{
		XMVECTOR vPos = XMLoadFloat2(&position);
		XMVECTOR plane = XMLoadFloat3(&g_vPlanes[i]);
		XMVECTOR dot = XMVector2Dot(vPos, plane);
		float dist;
		XMStoreFloat(&dist, dot);
		
		acceleration.x += min(dist, 0) * -g_fWallStiffness * g_vPlanes[i].x;
		acceleration.y += min(dist, 0) * -g_fWallStiffness * g_vPlanes[i].y;
	}
	acceleration.x += g_vGravity.x;
	acceleration.y += g_vGravity.y;

	// Integrate
	velocity.x += g_fTimeStep.x * acceleration.x;
	velocity.y += g_fTimeStep.y * acceleration.y;
	position.x += g_fTimeStep.x * velocity.x;
	position.y += g_fTimeStep.y * velocity.y;

	// Update
	ParticlesRW[P_ID].vPosition = position;
	ParticlesRW[P_ID].vVelocity = velocity;
}