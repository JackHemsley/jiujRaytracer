#include "vec3.h"

double vec3::getx() const { return this->x; }
double vec3::gety() const { return this->y; }
double vec3::getz() const { return this->z; }

double vec3::length() const{
	return sqrt(this->getx() * this->getx() + this->gety() * this->gety() + this->getz() * this->getz());
}

vec3 vec3::normalise() const {
	double len = this->length();
	return vec3(this->getx() / len, this->gety() / len, this->getz() / len);
}

double vec3::dot(const vec3& a) const {
	return a.getx() * x + a.gety() * y + a.getz() * z;
}

vec3 vec3::cross(const vec3& a) const {
	return vec3(a.gety() * z - a.getz() * y,
		a.getz() * x - a.getx() * z,
		a.getx() * y - a.gety() * x
	);
}

vec3 vec3::operator+ (const vec3& a) {
	return vec3(this->getx() + a.getx(), this->gety() + a.gety(), this->getz() + a.getz());
}

const vec3 vec3::operator+ (const vec3& a) const {
	return vec3(this->getx() + a.getx(), this->gety() + a.gety(), this->getz() + a.getz());
}

vec3 vec3::operator- (const vec3& a) {
	return vec3(this->getx() - a.getx(), this->gety() - a.gety(), this->getz() - a.getz());
}

const vec3 vec3::operator- (const vec3& a) const {
	return vec3(this->getx() - a.getx(), this->gety() - a.gety(), this->getz() - a.getz());
}

vec3 vec3::operator* (const vec3& a) {
	return vec3(this->getx() * a.getx(), this->gety() * a.gety(), this->getz() * a.getz());
}

const vec3 vec3::operator* (const vec3& a) const {
	return vec3(this->getx() + a.getx(), this->gety() + a.gety(), this->getz() + a.getz());
}

vec3 vec3::operator/ (const vec3& a) {
	return vec3(this->getx() / a.getx(), this->gety() / a.gety(), this->getz() / a.getz());
}

const vec3 vec3::operator/ (const vec3& a) const {
	return vec3(this->getx() + a.getx(), this->gety() + a.gety(), this->getz() + a.getz());
}

vec3 vec3::operator / (const double a) {
	return vec3(this->getx() / a, this->gety() / a, this->getz() / a);
}

const vec3 vec3::operator/ (const double a) const {
	return vec3(this->getx() + a, this->gety() + a, this->getz() + a);
}


bool vec3::operator==(const vec3& a) {
	return this->getx() == a.getx() && this->gety() == a.gety() && this->getz() == a.getz();
}