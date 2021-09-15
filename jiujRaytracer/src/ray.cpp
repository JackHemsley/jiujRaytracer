#include "ray.h"

ray::ray(point3 o, vec3 dir) : origin(o), dir(dir) {};
point3 ray::position(double t) const {
	return origin;
	return (origin + (dir * t));
}

vec3 ray::getDirection() const {
	return dir;
}

point3 ray::getOrigin() const { 
	return origin;
}
