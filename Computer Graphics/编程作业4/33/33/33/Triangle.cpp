#include "pch.h"
#include "Triangle.h"
#include "vecmath/include/Matrix3f.h"


Triangle::Triangle()
{
}


Triangle::Triangle(Vec3f &a, Vec3f &b, Vec3f &c, Material *m)
{
	m_a = a;
	m_b = b;
	m_c = c;
	m_material = m;
	Vec3f::Cross3(m_normal, a - b, a - c);
	m_normal.Normalize();
}

Triangle::~Triangle()
{
}

bool Triangle::intersect(const Ray &r, Hit &h, float tmin)
{
	float A = m_a.x() - m_b.x();
	float B = m_a.y() - m_b.y();
	float C = m_a.z() - m_b.z();
	float D = m_a.x() - m_c.x();
	float E = m_a.y() - m_c.y();
	float F = m_a.z() - m_c.z();
	float G = r.getDirection().x();
	float H = r.getDirection().y();
	float I = r.getDirection().z();
	float J = m_a.x() - r.getOrigin().x();
	float K = m_a.y() - r.getOrigin().y();
	float L = m_a.z() - r.getOrigin().z();
	float acramer = Matrix3f(A,D,G,
							B,E,H,
							C,F,I).determinant();
	float beta = Matrix3f(J,D,G,
						K, E, H,
						L, F, I).determinant() / acramer;
	float gamma = Matrix3f(A, J, G,
						B, K, H,
						C, L, I).determinant() / acramer;
	if (beta > 0 && gamma > 0 && (beta + gamma) < 1) {
		float t = Matrix3f(A, D, J,
						B, E, K,
						C, F, L).determinant() / acramer;
		if (t > tmin && t < h.getT()) {
			h.set(t, m_material, m_normal, r);
			return true;
		}
	}
	return false;
}
