#include "pch.h"
#include "Transform.h"


Transform::Transform()
{
}


Transform::Transform(Matrix &m, Object3D *o)
{
	m_matrix = m;
	m_obj = o;
}

Transform::~Transform()
{
}

bool Transform::intersect(const Ray &r, Hit &h, float tmin)
{
	Vec3f origin = r.getOrigin();
	Vec3f direction = r.getDirection();
	Matrix M = m_matrix;

	if (M.Inverse()) {
		M.Transform(origin);
		M.TransformDirection(direction);

		Ray r2(origin, direction);
		if (m_obj->intersect(r2, h, tmin)) {
			Vec3f n = h.getNormal();
			M.Transpose();
			M.TransformDirection(n);
			n.Normalize();
			h.set(h.getT(), h.getMaterial(), n, r);
			return true;
		}
	}
	return false;
}
