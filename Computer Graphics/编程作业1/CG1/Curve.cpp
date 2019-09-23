#include "stdafx.h"
#include "Curve.h"


Curve::Curve()
{
}

Curve::~Curve()
{
	
}

Curve::Curve(int num_vertices):Spline(num_vertices) {
	
}

void Curve::Paint(ArgParser *args) {
	//printVertices();
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
	//画曲线->Bezier
	if (getFlag() == 0) {
		glLineWidth(3);
		glBegin(GL_LINES);
		glColor3f(0, 1, 0);
		int curve_tessellation = args->curve_tessellation;
		int times = (getNumVertices() - 1) / 3;
		for (size_t i = 0; i < times; i++)
		{
			paintBezier(i*3, curve_tessellation);
		}
		//float stepSize = 1.0f / curve_tessellation;
		//float *xyz = new float[3];
		//bezierXYZ(0*stepSize, xyz,0);
		//glVertex3fv(xyz);
		//for (size_t i = 1; i < curve_tessellation; i++)
		//{
		//	bezierXYZ(i*stepSize, xyz,0);
		//	glVertex3fv(xyz);
		//	bezierXYZ(i*stepSize, xyz,0);
		//	glVertex3fv(xyz);
		//	//glVertex3f(bezierX(i*stepSize), bezierY(i*stepSize), bezierZ(i*stepSize));
		//}
		//bezierXYZ(curve_tessellation*stepSize, xyz,0);
		//glVertex3fv(xyz);
		//delete xyz;
		glEnd();
	}
	//画曲线->BSpline
	if (getFlag() == 1) {
		glLineWidth(3);
		glBegin(GL_LINES);
		glColor3f(0, 1, 0);
		int curve_tessellation = args->curve_tessellation;
		int times = getNumVertices() - 3;
		for (size_t i = 0; i < times; i++)
		{
			paintBSpline(i, curve_tessellation);
		}
		//glVertex3f(vertices->at(0).x(), vertices->at(0).y(), vertices->at(0).z());
		//float stepSize = 1.0f / curve_tessellation;
		//float *xyz = new float[3];
		//bSplineXYZ(0*stepSize, xyz,0);
		//glVertex3fv(xyz);
		//for (size_t i = 1; i < curve_tessellation; i++)
		//{
		//	bSplineXYZ(i*stepSize, xyz,0);
		//	glVertex3fv(xyz);
		//	glVertex3fv(xyz);
		//	//glVertex3f(bezierX(i*stepSize), bezierY(i*stepSize), bezierZ(i*stepSize));
		//}
		//bSplineXYZ(curve_tessellation*stepSize, xyz,0);
		//glVertex3fv(xyz);
		//delete xyz;
		glEnd();
	}
	//画控制点
	glPointSize(6.0f);
	glBegin(GL_POINTS);
	glColor3f(1, 0, 0);
	for (size_t i = 0; i < getNumVertices(); i++)
	{
		glVertex3f(getVertex(i).x(), getVertex(i).y(), getVertex(i).z());
	}
	glEnd();
}

void Curve::paintBezier(int index,int curve_tessellation) {
	float stepSize = 1.0f / curve_tessellation;
	float *xyz = new float[3];
	bezierXYZ(0 * stepSize, xyz,index);
	glVertex3fv(xyz);
	for (size_t i = 1; i < curve_tessellation; i++)
	{
		bezierXYZ(i*stepSize, xyz,index);
		glVertex3fv(xyz);
		glVertex3fv(xyz);
	}
	bezierXYZ(curve_tessellation*stepSize, xyz,index);
	glVertex3fv(xyz);
	delete xyz;
}
void Curve::paintBSpline(int index, int curve_tessellation) {
	float stepSize = 1.0f / curve_tessellation;
	float *xyz = new float[3];
	bSplineXYZ(0 * stepSize, xyz, index);
	glVertex3fv(xyz);
	for (size_t i = 1; i < curve_tessellation; i++)
	{
		bSplineXYZ(i*stepSize, xyz, index);
		glVertex3fv(xyz);
		glVertex3fv(xyz);
	}
	bSplineXYZ(curve_tessellation*stepSize, xyz, index);
	glVertex3fv(xyz);
	delete xyz;
}



//float Curve::bezierX(float t) {
//	return pow(1 - t, 3)*vertices->at(0).x() + 3 * t*pow(1 - t, 2)*vertices->at(1).x() + 3 * pow(t, 2)*(1 - t)*vertices->at(2).x() + pow(t, 3)*vertices->at(3).x();
//}
//float Curve::bezierY(float t) {
//	return pow(1 - t, 3)*vertices->at(0).y() + 3 * t*pow(1 - t, 2)*vertices->at(1).y() + 3 * pow(t, 2)*(1 - t)*vertices->at(2).y() + pow(t, 3)*vertices->at(3).y();
//}
//float Curve::bezierZ(float t) {
//	return pow(1 - t, 3)*vertices->at(0).z() + 3 * t*pow(1 - t, 2)*vertices->at(1).z() + 3 * pow(t, 2)*(1 - t)*vertices->at(2).z() + pow(t, 3)*vertices->at(3).z();
//}