#pragma once
#include "arg_parser.h"
#include "triangle_mesh.h"
#include <map>
#include <GL/glut.h>
class Spline
{
public:
	Spline();
	~Spline();
	// 用于画图的FOR VISUALIZATION
	virtual void Paint(ArgParser *args);

	// 用于实现样条类型转换的FOR CONVERTING BETWEEN SPLINE TYPES
	virtual void OutputBezier(FILE *file);
	virtual void OutputBSpline(FILE *file);

	// 用于得到控制点的FOR CONTROL POINT PICKING
	virtual int getNumVertices();
	virtual Vec3f getVertex(int i);

	// 用于编辑操作的FOR EDITING OPERATIONS
	virtual void moveControlPoint(int selectedPoint, float x, float y);
	virtual void addControlPoint(int selectedPoint, float x, float y);
	virtual void deleteControlPoint(int selectedPoint);

	// 用于产生三角形的FOR GENERATING TRIANGLES
	virtual TriangleMesh* OutputTriangles(ArgParser *args);
	virtual TriangleMesh* OutputBezierTriangles(ArgParser *args);
	virtual TriangleMesh* OutputBSplineTriangles(ArgParser *args);


	//---------------------------
	Spline(int num_vertices);
	void set(int i, Vec3f v);

	void setFlag(int _flag){ this->flag = _flag; }
	int getFlag() {return flag;}

	void printVertices() {
		printf("-------------------------------\n");
		for (size_t i = 0; i < getNumVertices(); i++)
		{
			printf("%f %f %f\n", getVertex(i).x(), getVertex(i).y(), getVertex(i).z());
		}
		printf("--------------------------------\n");
	}
	void bezierXYZ(float t, float *xyz, int index);
	void bSplineXYZ(float t, float *xyz, int index);

private:
	int num_vertices;
	map<int, Vec3f> vertices;

	int flag;//0->bezier 1->BSpline
};

