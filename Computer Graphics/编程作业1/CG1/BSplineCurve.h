#pragma once
#include "Curve.h"
#include "matrix.h"
class BSplineCurve :
	public Curve
{
public:
	BSplineCurve();
	BSplineCurve(int num_vertices);
	~BSplineCurve();
	//void set(int i, Vec3f v);
	void OutputBezier(FILE *file);
	void OutputBSpline(FILE *file);
};

