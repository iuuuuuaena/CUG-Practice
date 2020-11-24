#pragma once
#include "Object3D.h"
#include "matrix.h"
class Transform :
	public Object3D
{
public:
	Transform();
	Transform(Matrix &m, Object3D *o);
	~Transform();

	virtual bool intersect(const Ray &r, Hit &h, float tmin);

protected:
	Object3D *m_obj;
	Matrix m_matrix;
};

