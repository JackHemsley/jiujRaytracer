#pragma once
#include <iostream>
#include "../vec3.h"


class point3
{

public:
	point3() : x(0), y(0), z(0) {}

	point3(double x, double y, double z) : x(x), y(y), z(z) {}

	point3(double coord) : x(coord), y(coord), z(coord) {}

	double getx() const;
	double gety() const;
	double getz() const;
	double distance(const point3& a, const point3& b);
	double distancesquared(const point3& a, const point3& b);

	friend std::ostream& operator<<(std::ostream& stream, const point3& m);
	point3 operator+ (const point3& a);
	const point3 operator+ (const point3& a) const;
	point3 operator- (const vec3& a);
	const point3 operator- (const vec3& a) const;
	vec3 operator- (const point3& a);
	const vec3 operator- (const point3& a) const;
	point3 operator* (const point3& a);
	const point3 operator* (const point3& a) const;
	point3 operator/ (const point3& a);
	const point3 operator/ (const point3& a) const;
	point3 operator/ (const double a);
	const point3 operator/ (const double a) const;
	bool operator== (const point3& a);

	point3& operator +=(const point3& other) {
		x += other.getx();
		y += other.gety();
		z += other.getz();
		return *this;
	}

	point3& operator -=(const point3& other) {
		x -= other.getx();
		y -= other.gety();
		z -= other.getz();
		return *this;
	}

	point3& operator *=(const point3& other) {
		x *= other.getx();
		y *= other.gety();
		z *= other.getz();
		return *this;
	}


	point3& operator /=(const point3& other) {
		x /= other.getx();
		y /= other.gety();
		z /= other.getz();
		return *this;
	}

	bool equal(const point3& a) {
		return this->getx() == a.getx() && this->gety() == a.gety() && this->getz() == a.getz();
	}

private:
	double x;
	double y;
	double z;

};

inline
std::ostream& operator <<(std::ostream& stream, point3& m) {
	stream << "x: " << m.getx() << " y: " << m.gety() << " z: " << m.getz();
	return stream;
}

inline
point3 operator* (const double a, const point3& b) {
	return point3(b.getx() * a, b.gety() * a, b.getz() * a);
}

inline
point3 operator+ (const point3 p, const vec3 v) {
	return point3(v.getx() + p.getx(), v.gety() + p.gety(), v.getz() + p.getz());
}

inline
point3 operator+ (const vec3 v, const point3 p) {
	return point3(v.getx() + p.getx(), v.gety() + p.gety(), v.getz() + p.getz());
}

