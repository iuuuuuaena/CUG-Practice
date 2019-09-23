#pragma once
#include "Surface.h"
#include "Curve.h"
class SurfaceOfRevolution :
	public Surface
{
public:
	SurfaceOfRevolution();
	SurfaceOfRevolution(Curve *c);
	~SurfaceOfRevolution();

	void Paint(ArgParser *args);
	TriangleMesh* OutputTriangles(ArgParser *args);


	void moveControlPoint(int selectedPoint, float x, float y) {
		curve->moveControlPoint(selectedPoint, x, y);
	}
	void addControlPoint(int selectedPoint, float x, float y) {
		curve->addControlPoint(selectedPoint, x, y);
	}
	void deleteControlPoint(int selectedPoint) {
		curve->deleteControlPoint(selectedPoint);
	}

	void OutputBezier(FILE *file) {
		curve->OutputBezier(file);
	}
	void OutputBSpline(FILE *file) {
		curve->OutputBSpline(file);
	}

	int getNumVertices() {
		return curve->getNumVertices();
	}
	Vec3f getVertex(int i) {
		return curve->getVertex(i);
	}

private:
	Curve * curve;
};

