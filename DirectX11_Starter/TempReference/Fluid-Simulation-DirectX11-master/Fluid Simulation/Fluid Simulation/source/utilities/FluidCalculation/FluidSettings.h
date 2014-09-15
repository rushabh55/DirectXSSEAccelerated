/********************************************************************
FluidSettings.h: A struct encompassing the settings required for a 
fluid calculator. Provides a method for getting a TwType for placing
on a Tweak Bar

Author:	Valentin Hinov
Date: 3/3/2014
*********************************************************************/

#ifndef _FLUIDSETTINGS_H
#define _FLUIDSETTINGS_H

#include "../math/MathUtils.h"

// Default parameters
#define DIMENSION 64.0f
#define TIME_STEP 0.1f
#define CONSTANT_INPUT_RADIUS 0.1f // as a percentage of total size
#define INTERACTION_IMPULSE_RADIUS 7.0f
#define OBSTACLES_IMPULSE_RADIUS 5.0f
#define JACOBI_ITERATIONS 10
#define VEL_DISSIPATION 0.995f
#define DENSITY_DISSIPATION 0.999f
#define TEMPERATURE_DISSIPATION 0.995f
#define SMOKE_BUOYANCY 1.0f
#define SMOKE_WEIGHT 0.013f
#define AMBIENT_TEMPERATURE 0.0f
#define CONSTANT_TEMPERATURE 3.0f
#define CONSTANT_DENSITY 1.0f
#define VORTICITY_STRENGTH 0.8f
#define CONSTANT_REACTION 1.0f
#define REACTION_DECAY 0.001f
#define REACTION_EXTINGUISHMENT 0.01f

enum SystemAdvectionType_t {
	NORMAL, 
	MACCORMARCK
};

enum FluidType_t {
	SMOKE,
	FIRE
};

enum ETwType;


struct FluidSettings {	
	Vector3 dimensions;	
	int jacobiIterations;
	float timeStep;
	SystemAdvectionType_t advectionType;
	float velocityDissipation;
	float temperatureDissipation;
	float constantTemperature;
	float densityDissipation;
	float constantDensityAmount;
	float densityWeight;
	float densityBuoyancy;
	float constantInputRadius;
	float vorticityStrength;
	Vector3 constantInputPosition;	// location of permanent density and temperature input as % of dimensions

	// fire only settings
	float constantReactionAmount;
	float reactionDecay;
	float reactionExtinguishment;

	FluidSettings(FluidType_t fluidType = SMOKE);
	inline FluidType_t GetFluidType() const { return mFluidType; }
	ETwType GetFluidSettingsTwType(); // for use on an AntTweakBar

private:
	FluidType_t mFluidType; // should not be changed after initialization
};


#endif