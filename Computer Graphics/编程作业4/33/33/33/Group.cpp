#include "pch.h"
#include "Group.h"


Group::Group()
{
}

Group::Group(int num)
{
	m_num = num;
	m_object3ds = new Object3D*[num];
	for (size_t i = 0; i < num; i++)
	{
		m_object3ds[i] = NULL;
	}
}


Group::~Group()
{
	delete[] m_object3ds;
}

void Group::addObject(int index, Object3D * obj)
{
	if (index<m_num)
	{
		m_object3ds[index] = obj;
	}
}

bool Group::intersect(const Ray & r, Hit & h, float tmin)
{
	bool res = false;
	for (size_t i = 0; i < m_num; i++)
	{
		if (m_object3ds[i]==NULL)
		{
			continue;
		}
		if (m_object3ds[i]->intersect(r,h,tmin))
		{
			res = true;
		}
	}
	return res;
}
