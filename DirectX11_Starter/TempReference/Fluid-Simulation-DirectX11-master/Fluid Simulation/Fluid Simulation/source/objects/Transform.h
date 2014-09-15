/***************************************************************
Transform Class: Provides a transform component to objects.

Author: Valentin Hinov
Date: 06/09/2013
Version: 1.0
**************************************************************/

#ifndef _TRANSFORM_H
#define _TRANSFORM_H

#include "Component.h"
#include "../utilities/math/MathUtils.h"

class Transform : public Component {
public:
	// Default constructor should not be used
	Transform() : Component(nullptr), position(0.0f), scale(1.0f) {
	}

	Transform(const GameObject * const gameObject) : Component(gameObject), position(0.0f), scale(1.0f){
	}

	Transform(const GameObject * const gameObject, Vector3 &position, Quaternion &qRotation, Vector3 &scale = Vector3(1.0f)) 
		: Component(gameObject), position(position),qRotation(qRotation),scale(scale){
		
	}

	Vector3 position;
	Vector3 scale;
	Quaternion qRotation;

	void GetTransformMatrixQuaternion(Matrix &matrix, bool scaling = true) {
		Matrix m;
		if (scaling) {
			m = Matrix::CreateScale(scale);
			matrix*=m;
		}
		m = Matrix::CreateFromQuaternion(qRotation);	
		matrix*=m;
		m = Matrix::CreateTranslation(position);
		matrix*=m;
	}

	~Transform(){}	
};

#endif