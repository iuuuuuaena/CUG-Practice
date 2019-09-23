#include "stdafx.h"
#include "Spline.h"


Spline::Spline()
{
}


Spline::~Spline()
{
	//delete vertices;
}

// 用于画图的FOR VISUALIZATION
void Spline::Paint(ArgParser *args) {

}

// 用于实现样条类型转换的FOR CONVERTING BETWEEN SPLINE TYPES
void Spline::OutputBezier(FILE *file){}
void Spline::OutputBSpline(FILE *file){}

// 用于得到控制点的FOR CONTROL POINT PICKING
int Spline::getNumVertices() { return num_vertices; }
Vec3f Spline::getVertex(int i) { return vertices.at(i); }

// 用于编辑操作的FOR EDITING OPERATIONS
void Spline::moveControlPoint(int selectedPoint, float x, float y){
	//getVertex(selectedPoint).Set(x, y, 0);
	//printf("move");
	Vec3f v(x, y, 0);
	vertices.erase(selectedPoint);
	vertices.insert(map<int, Vec3f>::value_type(selectedPoint, v));
}
void Spline::addControlPoint(int selectedPoint, float x, float y){
	if (getFlag()==0)
	{
		return;
	}
	if (getFlag()==1)
	{
		Vec3f v(x, y, 0);
		//set(getNumVertices(), getVertex(getNumVertices() - 1));
		for (size_t i = getNumVertices(); i > selectedPoint; i--)
		{
			vertices.erase(i);
			set(i, getVertex(i - 1));
		}
		vertices.erase(selectedPoint);
		set(selectedPoint, v);
		num_vertices++;
	}
}
void Spline::deleteControlPoint(int selectedPoint){
	if (getFlag()==0)
	{
		return;
	}
	if (getFlag()==1)
	{
		num_vertices--;
		for (size_t i = selectedPoint; i < getNumVertices(); i++)
		{
			vertices.erase(i);
			set(i, getVertex(i + 1));
		}
		vertices.erase(getNumVertices());
	}
}

Spline::Spline(int num_vertices) {
	this->num_vertices = num_vertices;
	//vertices = new map<int, Vec3f>;
}
void Spline::set(int i, Vec3f v) {
	vertices.insert(map<int, Vec3f>::value_type(i, v));
}

// 用于产生三角形的FOR GENERATING TRIANGLES
TriangleMesh* Spline::OutputTriangles(ArgParser *args) {
	//Bezier
	if (getFlag()==0)
	{
		return this->OutputBezierTriangles(args);
	}
	//BSpline
	if (getFlag()==1)
	{
		return this->OutputBSplineTriangles(args);
	}
	return NULL;
}

TriangleMesh* Spline::OutputBezierTriangles(ArgParser *args) {
	int num_line = (getNumVertices() - 1) / 3;//一条线由num_line条Bezier线组成
	int num_verts = (num_line*(args->curve_tessellation)+1)*args->revolution_tessellation;
	int num_tris = num_line * args->curve_tessellation*args->revolution_tessellation*2;
	TriangleMesh *mesh = new TriangleMesh(num_verts, num_tris);
	int curve_tessellation = args->curve_tessellation;


	float stepSize = 1.0f / curve_tessellation;
	float stepR = 2 * 3.1415926535897932 / args->revolution_tessellation;
	float *xyz = new float[3];
	int floor=0;
	for (size_t i = 0; i < num_line; i++)
	{
		for (size_t j = 0; j < curve_tessellation; j++)
		{
			bezierXYZ(j*stepSize, xyz, i*3);
			for (size_t k = 0; k < args->revolution_tessellation;k++)
			{
				Vec3f v(xyz[0] * cos(stepR*k), xyz[1], xyz[0] * sin(stepR*k));
				mesh->SetVertex(floor*args->revolution_tessellation + k, v);
			}
			floor++;
		}
	}
	bezierXYZ(1, xyz, (num_line-1) * 3);
	for (size_t k = 0; k < args->revolution_tessellation; k++)
	{
		Vec3f v(xyz[0] * cos(stepR*k), xyz[1], xyz[0] * sin(stepR*k));
		mesh->SetVertex(floor*args->revolution_tessellation + k, v);
	}
	delete xyz;
	int u_tess = floor;
	int v_tess = args->revolution_tessellation;
	for (int i = 0; i < u_tess; i++) {
		for (int j = 0; j < v_tess; j++) {
			int index = (i*v_tess + j) * 2;
			int a1 = i * (v_tess ) + j;
			int a2 = (i + 1)*(v_tess ) + j;
			int b1 = i * (v_tess ) + (j + 1);
			int b2 = (i + 1)*(v_tess ) + (j + 1);
			if (j==v_tess-1)
			{
				b1 = i * (v_tess);
				b2 = (i + 1)*(v_tess);
			}
			mesh->SetTriangle(index, a1, b1, a2);
			mesh->SetTriangle(index + 1, b1, b2, a2);
		}
	}
	return mesh;
}

TriangleMesh* Spline::OutputBSplineTriangles(ArgParser *args) {
	
	int num_line = getNumVertices()-3;//一条线由num_line条Bezier线组成
	int num_verts = (num_line*(args->curve_tessellation) + 1)*args->revolution_tessellation;
	int num_tris = num_line * args->curve_tessellation*args->revolution_tessellation * 2;
	TriangleMesh *mesh = new TriangleMesh(num_verts, num_tris);
	int curve_tessellation = args->curve_tessellation;

	float stepSize = 1.0f / curve_tessellation;
	float stepR = 2 * 3.1415926535897932 / args->revolution_tessellation;
	float *xyz = new float[3];
	int floor = 0;
	for (size_t i = 0; i < num_line; i++)
	{
		for (size_t j = 0; j < curve_tessellation; j++)
		{
			bSplineXYZ(j*stepSize, xyz, i);
			for (size_t k = 0; k < args->revolution_tessellation; k++)
			{
				Vec3f v(xyz[0] * cos(stepR*k), xyz[1], xyz[0] * sin(stepR*k));
				mesh->SetVertex(floor*args->revolution_tessellation + k, v);
			}
			floor++;
		}
	}
	bSplineXYZ(1, xyz, num_line - 1);
	for (size_t k = 0; k < args->revolution_tessellation; k++)
	{
		Vec3f v(xyz[0] * cos(stepR*k), xyz[1], xyz[0] * sin(stepR*k));
		mesh->SetVertex(floor*args->revolution_tessellation + k, v);
	}
	delete xyz;
	int u_tess = floor;
	int v_tess = args->revolution_tessellation;
	for (int i = 0; i < u_tess; i++) {
		for (int j = 0; j < v_tess; j++) {
			int index = (i*v_tess + j) * 2;
			int a1 = i * (v_tess)+j;
			int a2 = (i + 1)*(v_tess)+j;
			int b1 = i * (v_tess)+(j + 1);
			int b2 = (i + 1)*(v_tess)+(j + 1);
			if (j == v_tess - 1)
			{
				b1 = i * (v_tess);
				b2 = (i + 1)*(v_tess);
			}
			mesh->SetTriangle(index, a1, b1, a2);
			mesh->SetTriangle(index + 1, b1, b2, a2);
		}
	}
	return mesh;
}

void Spline::bezierXYZ(float t, float *xyz, int index) {
	xyz[0] = pow(1 - t, 3)*getVertex(index).x() + 3 * t*pow(1 - t, 2)*getVertex(index + 1).x() + 3 * pow(t, 2)*(1 - t)*getVertex(2 + index).x() + pow(t, 3)*getVertex(3 + index).x();
	xyz[1] = pow(1 - t, 3)*getVertex(index).y() + 3 * t*pow(1 - t, 2)*getVertex(index + 1).y() + 3 * pow(t, 2)*(1 - t)*getVertex(2 + index).y() + pow(t, 3)*getVertex(3 + index).y();
	xyz[2] = pow(1 - t, 3)*getVertex(index).z() + 3 * t*pow(1 - t, 2)*getVertex(1 + index).z() + 3 * pow(t, 2)*(1 - t)*getVertex(2 + index).z() + pow(t, 3)*getVertex(3 + index).z();
}
void Spline::bSplineXYZ(float t, float *xyz, int index) {
	xyz[0] = pow(1 - t, 3) / 6 * getVertex(0 + index).x() + (3 * pow(t, 3) - 6 * pow(t, 2) + 4) / 6 * getVertex(1 + index).x() + (-3 * pow(t, 3) + 3 * pow(t, 2) + 3 * t + 1) / 6 * getVertex(2 + index).x() + pow(t, 3) / 6 * getVertex(3 + index).x();
	xyz[1] = pow(1 - t, 3) / 6 * getVertex(0 + index).y() + (3 * pow(t, 3) - 6 * pow(t, 2) + 4) / 6 * getVertex(1 + index).y() + (-3 * pow(t, 3) + 3 * pow(t, 2) + 3 * t + 1) / 6 * getVertex(2 + index).y() + pow(t, 3) / 6 * getVertex(3 + index).y();
	xyz[2] = pow(1 - t, 3) / 6 * getVertex(0 + index).z() + (3 * pow(t, 3) - 6 * pow(t, 2) + 4) / 6 * getVertex(1 + index).z() + (-3 * pow(t, 3) + 3 * pow(t, 2) + 3 * t + 1) / 6 * getVertex(2 + index).z() + pow(t, 3) / 6 * getVertex(3 + index).z();
}