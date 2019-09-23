#pragma once
#include "Surface.h"
class BezierPatch :
	public Surface
{
public:
	BezierPatch();
	~BezierPatch();

	Vec3f bezierXYZ(float t, Vec3f a, Vec3f b, Vec3f c, Vec3f d);
	void set(int i, Vec3f v);
	TriangleMesh* OutputTriangles(ArgParser *args);

	void Paint(ArgParser *args);

	Vec3f getVertex(int i,int j) {
		return vertices[i][j];
	}
	Vec3f getVertex(int i) {
		return vertices[i / 4][i % 4];
	}
	int getNumVertices() {
		return num_vertices;
	}
private:
	Vec3f vertices[4][4];
	int num_vertices=16;
};

