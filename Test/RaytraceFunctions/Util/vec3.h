#pragma once
#include "math.h"

class vec3
{
public:
	vec3() : x(0), y(0), z(0) {}

	vec3(double x, double y, double z) : x(x), y(y), z(z) {}

	vec3(double coord) : x(coord), y(coord), z(coord) {}

	double getx() const;
	double gety() const;
	double getz() const;
	double length() const;
	vec3 normalise();
	vec3 cross();

	double dot(const vec3& a, const vec3& b);

	vec3 operator+ (const vec3& a);
	vec3 operator- (const vec3& a);
	vec3 operator* (const vec3& a);
	vec3 operator* (const double a);
	vec3 operator/ (const vec3& a);
	vec3 operator/ (const double a);
	bool operator== (const vec3& a);

	vec3& operator +=(const vec3& other) {
		x += other.getx();
		y += other.gety();
		z += other.getz();
		return *this;
	}

	vec3& operator -=(const vec3& other) {
		x -= other.getx();
		y -= other.gety();
		z -= other.getz();
		return *this;
	}

	vec3&operator *=(const vec3& other) {
		x *= other.getx();
		y *= other.gety();
		z *= other.getz();
		return *this;
	}


	vec3& operator /=(const vec3& other) {
		x /= other.getx();
		y /= other.gety();
		z /= other.getz();
		return *this;
	}

	bool equal(const vec3& a) {
		return this->getx() == a.getx() && this->gety() == a.gety() && this->getz() == a.getz();
	}

private:
	double x;
	double y;
	double z;

};
