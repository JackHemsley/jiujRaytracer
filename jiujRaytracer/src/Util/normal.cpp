#include "normal.h"
#include <math.h>

double normal::getx() const { return this->x; }
double normal::gety() const { return this->y; }
double normal::getz() const { return this->z; }


double normal::length() const {
	return sqrt(this->getx() * this->getx() + this->gety() * this->gety() + this->getz() * this->getz());
}

normal normal::normalise() {
	double len = this->length();
	return normal(this->getx() / len, this->gety() / len, this->getz() / len);
}

vec3 normal::normalToVec3() const {
	return vec3(x, y, z);
}

normal normal::operator+ (const normal& a) {
	return normal(this->getx() + a.getx(), this->gety() + a.gety(), this->getz() + a.getz());
}

const normal normal::operator+ (const normal& a) const {
	return normal(this->getx() + a.getx(), this->gety() + a.gety(), this->getz() + a.getz());
}

normal normal::operator- (const normal& a) {
	return normal(this->getx() - a.getx(), this->gety() - a.gety(), this->getz() - a.getz());
}

const normal normal::operator- (const normal& a) const {
	return normal(this->getx() + a.getx(), this->gety() + a.gety(), this->getz() + a.getz());
}

normal normal::operator* (const normal& a) {
	return normal(this->getx() * a.getx(), this->gety() * a.gety(), this->getz() * a.getz());
}

const normal normal::operator* (const normal& a) const {
	return normal(this->getx() + a.getx(), this->gety() + a.gety(), this->getz() + a.getz());
}

normal normal::operator/ (const normal& a) {
	return normal(this->getx() / a.getx(), this->gety() / a.gety(), this->getz() / a.getz());
}

const normal normal::operator/ (const normal& a) const {
	return normal(this->getx() + a.getx(), this->gety() + a.gety(), this->getz() + a.getz());
}

normal normal::operator / (const double a) {
	return normal(this->getx() / a, this->gety() / a, this->getz() / a);
}

const normal normal::operator/ (const double a) const {
	return normal(this->getx() + a, this->gety() + a, this->getz() + a);
}


bool normal::operator==(const normal& a) {
	return this->getx() == a.getx() && this->gety() == a.gety() && this->getz() == a.getz();
}