#include "point.h"

point::point(double a,double b,double c, double d, double e, double f) :jdd(a), jdm(b),jds(c),wdd(d),wdm(e),wds(f) {
    this->jd = jdd + (jdm / 60) + (jds / 3600);
    this->wd = wdd + (wdm / 60) + (wds / 3600);
}

double point::rad(double angle) {
    return 3.14 * angle/180.0;
}
