#pragma once
#include "Object3D.h"
#include <vector>
class Group :
	public Object3D
{
public:
	Group();
	Group(int num);
	~Group();

	void addObject(int index, Object3D *obj);
	bool intersect(const Ray &r, Hit &h, float tmin);

protected:
	Object3D** m_object3ds;
	int m_num;
	//vector<Object3D*> m_object3ds;
};

