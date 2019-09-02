#include "earth.h"

earth::    earth(double a, double b, double c, double d, double e, double f, double g, double h, double i, double j, double k, double l) :point1(a, b,c,d,e,f), point2(g,h,i,j,k,l){}

double earth::dis() {
    double a = point1.rad(point1.jd) - point2.rad(point2.jd);
    double b = point1.rad(point1.wd) - point2.rad(point2.wd);
    double s = 2 * 6371 * asin(sqrt(pow(sin(a / 2), 2) + cos(point1.rad(point1.wd)) * cos(point2.rad(point2.wd)) * pow(sin(b / 2), 2)));
    return s;
}

bool earth::check(){
    if(point1.jd>=0&&point1.jd<=180&&point1.wd>=0&&point1.wd<=90&&point2.jd>=0&&point2.jd<=180&&point2.wd>=0&&point2.wd<=90)
        return true;
    else {
        return false;
    }
}
