#pragma once
#include "Camera.h"
class OrthographicCamera :
	public Camera
{
public:
	OrthographicCamera();
	OrthographicCamera(Vec3f center, Vec3f dirction, Vec3f up, float size);
	~OrthographicCamera();
	virtual Ray generateRay(Vec2f point);
	virtual float getTMin() const;

protected:
	Vec3f m_center;
	Vec3f m_up;
	Vec3f m_horizontal;
	Vec3f m_direction;
	float m_size;
};

