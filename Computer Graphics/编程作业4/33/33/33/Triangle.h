#pragma once
#include "Object3D.h"
class Triangle :
	public Object3D
{
public:
	Triangle();
	Triangle(Vec3f &a, Vec3f &b, Vec3f &c, Material *m);
	~Triangle();

	virtual bool intersect(const Ray &r, Hit &h, float tmin);
protected:
	Vec3f m_a;
	Vec3f m_b;
	Vec3f m_c;
	Vec3f m_normal;
};

