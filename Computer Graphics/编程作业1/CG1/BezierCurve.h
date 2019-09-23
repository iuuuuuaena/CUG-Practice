#pragma once
#include "Curve.h"
#include "matrix.h"
class BezierCurve :
	public Curve
{
public:
	BezierCurve();
	BezierCurve(int num_vertices);
	~BezierCurve();

	void OutputBezier(FILE *file);
	void OutputBSpline(FILE * file);
	//void set(int i, Vec3f v);
};

