#pragma once
#include <iostream>
#include "vec3.h"

class normal
{
public:
	normal() : x(0), y(0), z(0) {}

	normal(double x, double y, double z) : x(x), y(y), z(z) {}

	normal(double coord) : x(coord), y(coord), z(coord) {}

	explicit normal(vec3 v) : x(v.getx()), y(v.gety()), z(v.getz()) {}

	double getx() const;
	double gety() const;
	double getz() const;
	double length() const;
	normal normalise();
	vec3 normalToVec3() const;

	friend std::ostream& operator<<(std::ostream& stream, const normal& m);
	normal operator+ (const normal& a);
	const normal operator+(const normal& a) const;
	normal operator- (const normal& a);
	const normal operator-(const normal& a) const;
	normal operator* (const normal& a);
	const normal operator*(const normal& a) const;
	normal operator/ (const normal& a);
	const normal operator/(const normal& a) const;
	normal operator/ (const double a);
	const normal operator/(const double a) const;
	bool operator== (const normal& a);


	normal& operator +=(const normal& other) {
		x += other.getx();
		y += other.gety();
		z += other.getz();
		return *this;
	}

	normal& operator -=(const normal& other) {
		x -= other.getx();
		y -= other.gety();
		z -= other.getz();
		return *this;
	}

	normal& operator *=(const normal& other) {
		x *= other.getx();
		y *= other.gety();
		z *= other.getz();
		return *this;
	}


	normal& operator /=(const normal& other) {
		x /= other.getx();
		y /= other.gety();
		z /= other.getz();
		return *this;
	}

	bool equal(const normal& a) {
		return this->getx() == a.getx() && this->gety() == a.gety() && this->getz() == a.getz();
	}

private:
	double x;
	double y;
	double z;


};

inline
std::ostream& operator <<(std::ostream& stream, normal& m) {
	stream << "x: " << m.getx() << " y: " << m.gety() << " z: " << m.getz();
	return stream;
}

inline
normal operator* (const double a, const normal& b) {
	return normal(b.getx() * a, b.gety() * a, b.getz() * a);
}