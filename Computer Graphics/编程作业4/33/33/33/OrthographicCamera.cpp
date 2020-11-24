#include "pch.h"
#include "OrthographicCamera.h"


OrthographicCamera::OrthographicCamera()
{
}

OrthographicCamera::OrthographicCamera(Vec3f center, Vec3f dirction, Vec3f up, float size)
{
	m_center = center;
	m_size = size;
	m_direction = dirction;
	m_direction.Normalize();
	if (up.Dot3(m_direction)!=0)
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


OrthographicCamera::~OrthographicCamera()
{
}

Ray OrthographicCamera::generateRay(Vec2f point)
{
	//Vec3f origin;
	//origin = m_center + (point.x() - 0.5f)*m_size*m_horizontal + (point.y() - 0.5f)*m_size*m_up;
	//return (Ray(origin, m_direction));
	Vec3f c = m_center + (point.x() - 0.5) * m_size * m_horizontal + (point.y() - 0.5) * m_size * m_up;
	return Ray(c, m_direction);
}

float OrthographicCamera::getTMin() const
{
	//return FLT_MIN;
	return -INT_MAX;
}
