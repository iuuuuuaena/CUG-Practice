#include "pch.h"
#include "Sphere.h"


Sphere::Sphere()
{
}

Sphere::Sphere(Vec3f center, float radius, Material * material)
	//:Object3D(material),m_radius(radius),m_center(center)
{
	m_material = material;
	m_radius = radius;
	m_center = center;
}


Sphere::~Sphere()
{
}

bool Sphere::intersect(const Ray & r, Hit & h, float tmin)
{
	Vec3f ray_origin = r.getOrigin() - m_center;//球心不一定在原点

	float a = r.getDirection().Dot3(r.getDirection());
	float b = 2.f*ray_origin.Dot3(r.getDirection());
	float c = ray_origin.Dot3(ray_origin) - m_radius * m_radius;

	if (b*b >= 4 * a*c) {
		float t1 = (-b + sqrt(b*b - 4 * a*c)) / (2.f*a);
		float t2 = (-b - sqrt(b*b - 4 * a*c)) / (2.f*a);
		if (t2 >= tmin&&t2 < h.getT()) {
			//h.set(t2, m_material, r);
			Vec3f normal = ray_origin + t2 * r.getDirection();
			h.set(t2, m_material, normal, r);
			return true;
		}
		if (t1>=tmin&&t1<h.getT())
		{
			//h.set(t1, m_material, r);
			Vec3f normal = ray_origin + t1 * r.getDirection();
			h.set(t1, m_material, normal, r);
			return true;
		}
	}
	return false;
}
