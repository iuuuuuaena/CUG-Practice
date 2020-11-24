#pragma once
#include "Object3D.h"
class Plane :
	public Object3D
{
public:
	Plane();
	Plane(Vec3f &normal, float d, Material *m);
	~Plane();

	virtual bool intersect(const Ray &r, Hit &h, float tmin);


protected:
	float m_d;
	Vec3f m_normal;
};

