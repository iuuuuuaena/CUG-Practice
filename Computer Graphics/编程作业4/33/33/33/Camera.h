#pragma once
#include "ray.h"

class Camera
{
public:
	Camera();
	~Camera();
	virtual Ray generateRay(Vec2f point) = 0;
	virtual float getTMin() const = 0;
};

