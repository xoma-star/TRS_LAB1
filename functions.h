#pragma once
#include <math.h>

double function(double x) {
	return cosh(2 * x);
}

double functionX(double v) {
	return 10 * v;
}

double functionV(double t) {
	return  (-4. / 16.7) * t / (cos(t * t) * cos(t * t));
}