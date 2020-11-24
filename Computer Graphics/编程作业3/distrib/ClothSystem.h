#ifndef CLOTHSYSTEM_H
#define CLOTHSYSTEM_H

#include <vecmath.h>
#include <vector>
#ifdef _WIN32
#include "GL/freeglut.h"
#else
#include <GL/glut.h>
#endif

#include "particleSystem.h"

class ClothSystem: public ParticleSystem
{
///ADD MORE FUNCTION AND FIELDS HERE
public:
	ClothSystem();
	ClothSystem(int n);
	vector<Vector3f> evalF(vector<Vector3f> state);
	
	void draw();
	int indexOf(int i, int j);
	Vector3f generateElasticity(Vector3f v1, Vector3f v2, float k_elasticity,float _r);
	void draw(int i1, int i2, int i3);

private:
	vector<Vector3f> forces;
	float mass;
	float r;
	int n;
};


#endif
