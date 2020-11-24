#include "pch.h"
#include "Plane.h"


Plane::Plane()
{
}


Plane::Plane(Vec3f &normal, float d, Material *m)
{
	m_d = d;
	m_material = m;
	m_normal = normal;
}

Plane::~Plane()
{
}

bool Plane::intersect(const Ray &r, Hit &h, float tmin)
{
	if (r.getDirection().Dot3(m_normal)==0)
	{
		return false;
	}
	float t = (m_d - m_normal.Dot3(r.getOrigin())) / m_normal.Dot3(r.getDirection());
	if (t > tmin&&t < h.getT()) {
		h.set(t, m_material, m_normal, r);
		return true;
	}
	return false;
}
