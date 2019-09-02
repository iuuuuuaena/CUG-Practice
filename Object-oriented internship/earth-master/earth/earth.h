#ifndef EARTH_H
#define EARTH_H
#include<point.h>

class earth
{
public:
    earth(double a, double b, double c, double d, double e, double f, double g, double h, double i, double j, double k, double l) ;
        double dis();
        bool check();
private:
        point point1, point2;
};

#endif // EARTH_H
