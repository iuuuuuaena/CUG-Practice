#include "stdafx.h"
#include "BezierCurve.h"


BezierCurve::BezierCurve()
{
}

BezierCurve::~BezierCurve()
{
}

BezierCurve::BezierCurve(int num_vertices) :Curve(num_vertices){
	this->setFlag(0);
}

void BezierCurve::OutputBezier(FILE * file)
{
	fprintf(file, "\nbezier\n");
	fprintf(file, "num_vertices %d\n", getNumVertices());
	for (size_t i = 0; i < getNumVertices(); i++)
	{
		fprintf(file, "%f %f %f\n", getVertex(i).x(), getVertex(i).y(), getVertex(i).z());
	}
}

void BezierCurve::OutputBSpline(FILE *file) {
	int num_line = (getNumVertices() - 1) / 3;
	int num_verts = num_line + 1;

	float *bezierToBSpline = new float[16]{ 6,0,0,0,-7,2,-1,2,2,-1,2,-7,0,0,0,6 };
	Matrix bezierToBSplineM(bezierToBSpline);
	delete bezierToBSpline;
	for (size_t i = 0; i < num_line; i++)
	{
		fprintf(file, "\nbspline\nnum_vertices %d\n", 4);
		int index = 3 * i;
		float *bezier = new float[12]{ 
			getVertex(index).x(),getVertex(index + 1).x(),getVertex(index + 2).x(),getVertex(index + 3).x(),
			getVertex(index).y(),getVertex(index + 1).y(),getVertex(index + 2).y(),getVertex(index + 3).y(),
			getVertex(index).z(),getVertex(index + 1).z(),getVertex(index + 2).z(),getVertex(index + 3).z(), };
		Matrix bezierM(bezier);
		Matrix res = bezierM * bezierToBSplineM;
		for (size_t i = 0; i < 4; i++)
		{
			fprintf(file, "%f %f %f\n", res.Get(i,0), res.Get(i,1), res.Get(i,2));
		}
		delete bezier;
	}
}

// void BezierCurve::OutputBSpline(FILE *file) {
// 	fprintf(file, "\nbspline\n");
// 	fprintf(file, "num_vertices %d\n", getNumVertices());
// 	float bezierToBSpline[4][4] = { { 6,0,0,0 },{ -7,2,-1,2 },{ 2,-1,2,-7 },{ 0,0,0,6 } };
// 	for (size_t i = 0; i < getNumVertices(); i++)
// 	{
// 		float x = 0, y = 0, z = 0;
// 		for (size_t j = 0; j < getNumVertices(); j++)
// 		{
// 			x += getVertex(j).x()*bezierToBSpline[j][i];
// 			y += getVertex(j).y()*bezierToBSpline[j][i];
// 			z += getVertex(j).z()*bezierToBSpline[j][i];
// 		}
// 		fprintf(file, "%f %f %f\n", x, y, z);
// 	}
// }
//void BezierCurve::set(int i, Vec3f v) {
//
//}