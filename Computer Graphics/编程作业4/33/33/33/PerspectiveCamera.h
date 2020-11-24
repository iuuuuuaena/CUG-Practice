#pragma once
#include "Camera.h"
class PerspectiveCamera :
	public Camera
{
public:
	PerspectiveCamera();
	PerspectiveCamera(Vec3f cer, Vec3f &direction, Vec3f &up, float angle);
	~PerspectiveCamera();

	virtual Ray generateRay(Vec2f point);
	virtual float getTMin() const;

protected:
	Vec3f m_center;
	Vec3f m_up;
	Vec3f m_direction;
	Vec3f m_horizontal;
	float m_angle;
};

