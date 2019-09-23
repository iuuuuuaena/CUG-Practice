#include "stdafx.h"
#include "BezierPatch.h"


BezierPatch::BezierPatch()
{
}


BezierPatch::~BezierPatch()
{
}

Vec3f BezierPatch::bezierXYZ(float t, Vec3f a, Vec3f b, Vec3f c,Vec3f d) {
	float x = pow(1 - t, 3)*a.x() + 3 * t*pow(1 - t, 2)*b.x() + 3 * pow(t, 2)*(1 - t)*c.x() + pow(t, 3)*d.x();
	float y = pow(1 - t, 3)*a.y() + 3 * t*pow(1 - t, 2)*b.y() + 3 * pow(t, 2)*(1 - t)*c.y() + pow(t, 3)*d.y();
	float z = pow(1 - t, 3)*a.z() + 3 * t*pow(1 - t, 2)*b.z() + 3 * pow(t, 2)*(1 - t)*c.z() + pow(t, 3)*d.z();
	return Vec3f(x, y, z);
}

void BezierPatch::set(int i, Vec3f v) {
	vertices[i / 4][i % 4] = v;
}

TriangleMesh* BezierPatch::OutputTriangles(ArgParser *args) {
	TriangleNet *net = new TriangleNet(args->patch_tessellation, args->patch_tessellation);
	float stepSize = 1.0f / args->patch_tessellation;
	for (size_t i = 0; i <= args->patch_tessellation; i++)
	{
		for (size_t j = 0; j <= args->patch_tessellation; j++)
		{
			Vec3f v = bezierXYZ(j*stepSize,
				bezierXYZ(i*stepSize, getVertex(0, 0), getVertex(0, 1), getVertex(0, 2), getVertex(0, 3)),
				bezierXYZ(i*stepSize, getVertex(1, 0), getVertex(1, 1), getVertex(1, 2), getVertex(1, 3)),
				bezierXYZ(i*stepSize, getVertex(2, 0), getVertex(2, 1), getVertex(2, 2), getVertex(2, 3)),
				bezierXYZ(i*stepSize, getVertex(3, 0), getVertex(3, 1), getVertex(3, 2), getVertex(3, 3))
			);
			net->SetVertex(i, j, v);
		}
	}
	return net;
}

void BezierPatch::Paint(ArgParser *args) {
	//控制点
	glPointSize(6.0f);
	glBegin(GL_POINTS);
	glColor3f(1, 0, 0);
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			glVertex3f(getVertex(i,j).x(), getVertex(i,j).y(), getVertex(i,j).z());
		}
	}
	glEnd();
	//画控制点的连线
	glLineWidth(2);
	glBegin(GL_LINES);
	glColor3f(0, 0, 1);
	glVertex3f(getVertex(0).x(), getVertex(0).y(), getVertex(0).z());
	for (size_t i = 1; i < getNumVertices() - 1; i++)
	{
		glVertex3f(getVertex(i).x(), getVertex(i).y(), getVertex(i).z());
		glVertex3f(getVertex(i).x(), getVertex(i).y(), getVertex(i).z());
	}
	glVertex3f(getVertex(getNumVertices() - 1).x(), getVertex(getNumVertices() - 1).y(), getVertex(getNumVertices() - 1).z());
	glEnd();
}