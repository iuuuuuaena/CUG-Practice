#include "pch.h"
#include "PerspectiveCamera.h"


PerspectiveCamera::PerspectiveCamera()
{
}


PerspectiveCamera::PerspectiveCamera(Vec3f cer, Vec3f &direction, Vec3f &up, float angle)
{
	m_center = cer;
	m_direction = direction;
	m_angle = angle;
	m_direction.Normalize();
	if (up.Dot3(m_direction) != 0)
	{
		Vec3f tmp;
		Vec3f::Cross3(tmp, up, m_direction);
		Vec3f::Cross3(m_up, m_direction, tmp);
	}
	else
	{
		m_up = up;
	}
	m_up.Normalize();
	Vec3f::Cross3(m_horizontal, m_direction, m_up);
	m_horizontal.Normalize();
}

PerspectiveCamera::~PerspectiveCamera()
{
}

Ray PerspectiveCamera::generateRay(Vec2f point)
{
	float dis = 0.5 / tanf(m_angle / 2.f);
	Vec3f direction = dis * m_direction + (point.x() - 0.5)*m_horizontal + (point.y() - 0.5)*m_up;
	direction.Normalize();
	return Ray(m_center, direction);
}

float PerspectiveCamera::getTMin()const
{
	return 0;
}
