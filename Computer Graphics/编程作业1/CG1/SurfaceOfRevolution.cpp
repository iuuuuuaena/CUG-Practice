#include "stdafx.h"
#include "SurfaceOfRevolution.h"


SurfaceOfRevolution::SurfaceOfRevolution()
{
}


SurfaceOfRevolution::~SurfaceOfRevolution()
{
}

SurfaceOfRevolution::SurfaceOfRevolution(Curve *c) {
	this->curve = c;
}

void SurfaceOfRevolution::Paint(ArgParser *args) {
	curve->Paint(args);
}

TriangleMesh* SurfaceOfRevolution::OutputTriangles(ArgParser *args) {
	return curve->OutputTriangles(args);
}