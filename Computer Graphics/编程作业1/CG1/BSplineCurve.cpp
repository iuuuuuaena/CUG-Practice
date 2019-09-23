#include "stdafx.h"
#include "BSplineCurve.h"


BSplineCurve::BSplineCurve()
{
}


BSplineCurve::~BSplineCurve()
{
}

BSplineCurve::BSplineCurve(int num_vertices):Curve(num_vertices) {
	this->setFlag(1);
}
//float bezierToBSpline[4][4] = { { 1.0 / 6,0,0,0 },{ 2.0 / 3,2.0 / 3,1.0 / 3,1.0 / 6 },{ 1.0 / 6,1.0 / 3,2.0 / 3,2.0 / 3 },{ 0,0,0,1.0 / 6 } };

void BSplineCurve::OutputBezier(FILE *file) {
	int num_line = getNumVertices()-3;
	int num_verts = 3*num_line+1;

	float *bSplineToBezier = new float[16]{ 1.0f / 6,0,0,0,
		2.0f / 3,2.0f / 3,1.0f / 3,1.0f / 6 ,
		1.0f / 6,1.0f / 3,2.0f / 3,2.0f / 3 ,
		0,0,0,1.0f / 6 };
	Matrix bezierToBSplineM(bSplineToBezier);
	delete bSplineToBezier;
	for (size_t i = 0; i < num_line; i++)
	{
		fprintf(file, "\nbezier\nnum_vertices %d\n", 4);
		float *bspline = new float[12]{
			getVertex(i).x(),getVertex(i + 1).x(),getVertex(i + 2).x(),getVertex(i + 3).x(),
			getVertex(i).y(),getVertex(i + 1).y(),getVertex(i + 2).y(),getVertex(i + 3).y(),
			getVertex(i).z(),getVertex(i + 1).z(),getVertex(i + 2).z(),getVertex(i + 3).z(), };
		Matrix bsplineM(bspline);
		Matrix res = bsplineM * bezierToBSplineM;
		for (size_t i = 0; i < 4; i++)
		{
			fprintf(file, "%f %f %f\n", res.Get(i, 0), res.Get(i, 1), res.Get(i, 2));
		}
		delete bspline;
	}
}

// void BSplineCurve::OutputBezier(FILE *file) {
// 	fprintf(file, "\nbezier\n");
// 	fprintf(file, "num_vertices %d\n", getNumVertices());
// 	float bezierToBSpline[4][4] = { { 1.0 / 6,0,0,0 },{ 2.0 / 3,2.0 / 3,1.0 / 3,1.0 / 6 },{ 1.0 / 6,1.0 / 3,2.0 / 3,2.0 / 3 },{ 0,0,0,1.0 / 6 } };
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

void BSplineCurve::OutputBSpline(FILE *file) {
	fprintf(file, "\nbspline\n");
	fprintf(file, "num_vertices %d\n", getNumVertices());
	for (size_t i = 0; i < getNumVertices(); i++)
	{
		fprintf(file, "%f %f %f\n", getVertex(i).x(), getVertex(i).y(), getVertex(i).z());
	}
}