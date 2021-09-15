#include "pointLight.h"

pointLight::pointLight() : pos(point3()), col(colour(1,1,1)) {}
pointLight::pointLight(point3 p, colour c) : pos(p), col(c) {}

point3 pointLight::getPosition() {
	return pos;
}

colour pointLight::getColour() {
	return col;
}

