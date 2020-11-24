#include "pch.h"
#include "Object3D.h"


Object3D::Object3D()
{
	m_material = NULL;
}

Object3D::Object3D(Material * material)
{
	m_material = material;
}


Object3D::~Object3D()
{
}


