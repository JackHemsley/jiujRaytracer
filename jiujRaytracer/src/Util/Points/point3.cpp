#include "point3.h"


double point3::getx() const { return this->x; }
double point3::gety() const { return this->y; }
double point3::getz() const { return this->z; }

double point3::distance(const point3& a, const point3& b) {
	return (a - b).length();
}

double point3::distancesquared(const point3& a, const point3& b) {
	return (a - b).length()* (a - b).length();
}

point3 point3::operator+ (const point3& a) {
	return point3(this->getx() + a.getx(), this->gety() + a.gety(), this->getz() + a.getz());
}

const point3 point3::operator+ (const point3& a) const {
	return point3(this->getx() + a.getx(), this->gety() + a.gety(), this->getz() + a.getz());
}

vec3 point3::operator- (const point3& a) {
	return vec3(this->getx() - a.getx(), this->gety() - a.gety(), this->getz() - a.getz());
}

const vec3 point3::operator- (const point3& a) const {
	return vec3(this->getx() + a.getx(), this->gety() + a.gety(), this->getz() + a.getz());
}

point3 point3::operator- (const vec3& a) {
	return point3(this->getx() - a.getx(), this->gety() - a.gety(), this->getz() - a.getz());
}

const point3 point3::operator- (const vec3& a) const {
	return point3(this->getx() + a.getx(), this->gety() + a.gety(), this->getz() + a.getz());
}

point3 point3::operator* (const point3& a) {
	return point3(this->getx() * a.getx(), this->gety() * a.gety(), this->getz() * a.getz());
}

const point3 point3::operator* (const point3& a) const {
	return point3(this->getx() + a.getx(), this->gety() + a.gety(), this->getz() + a.getz());
}

point3 point3::operator/ (const point3& a) {
	return point3(this->getx() / a.getx(), this->gety() / a.gety(), this->getz() / a.getz());
}

const point3 point3::operator/ (const point3& a) const {
	return point3(this->getx() / a.getx(), this->gety() / a.gety(), this->getz() / a.getz());
}

point3 point3::operator / (const double a) {
	return point3(this->getx() / a, this->gety() / a, this->getz() / a);
}

const point3 point3::operator/ (const double a) const {
	return point3(this->getx() / a, this->gety() / a, this->getz() / a);
}

bool point3::operator==(const point3& a) {
	return this->getx() == a.getx() && this->gety() == a.gety() && this->getz() == a.getz();
}