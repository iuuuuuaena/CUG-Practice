#ifndef POINT_H
#define POINT_H
#include <cmath>

class point
{
public:
    point(double a,double b,double c, double d, double e, double f);
           double rad(double angle);
           double jd, wd;
           double jdd, jdm, jds;
           double wdd, wdm, wds;
};

#endif // POINT_H
