#pragma once
#include "Spline.h"
using namespace std;
class Curve :
	public Spline
{
public:
	Curve();
	~Curve();

	Curve(int num_vertices);
	
	void Paint(ArgParser *args);
	
	
	void paintBezier(int index,int curve_tessellation);//画一条从index开始的bezier
	void paintBSpline(int index,int curve_tessellation);//画一条从index开始的BSpline

private:

	//float bezierX(float t);
	//float bezierY(float t);
	//float bezierZ(float t);

};

