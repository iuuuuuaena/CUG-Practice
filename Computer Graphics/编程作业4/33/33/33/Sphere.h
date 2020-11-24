#pragma once
#include "Object3D.h"
#include "vectors.h"
class Sphere :
	public Object3D
{
public:
	Sphere();
	Sphere(Vec3f center, float radius, Material *material);
	~Sphere();
	virtual bool intersect(const Ray &r, Hit &h, float tmin);

private:
	Vec3f m_center;
	float m_radius;
};

