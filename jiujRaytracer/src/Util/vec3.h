#pragma once
#include <assert.h>
#include <iostream>
#include <math.h>

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
	vec3 normalise() const;
	double dot(const vec3& a) const;
	vec3 cross(const vec3& a) const;

	friend std::ostream& operator<<(std::ostream& stream, const vec3& m);
	vec3 operator+ (const vec3& a);
	const vec3 operator+(const vec3& a) const;
	vec3 operator- (const vec3& a);
	const vec3 operator-(const vec3& a) const;
	vec3 operator* (const vec3& a);
	const vec3 operator*(const vec3& a) const;
	vec3 operator/ (const vec3& a);
	const vec3 operator/(const vec3& a) const;
	vec3 operator/ (const double a);
	const vec3 operator/(const double a) const;
	bool operator== (const vec3& a);

	double operator[](int i) {
		assert(i >= 0 && i <= 2);
		if (i == 0) {
			return this->x;
		}
		if (i == 1) {
			return this->y;
		}
		return this->z;
		
	}

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

inline
std::ostream& operator <<(std::ostream& stream, vec3& m) {
	stream << "x: " << m.getx() << " y: " << m.gety() << " z: " << m.getz();
	return stream;
}

inline
vec3 operator* (const double a, const vec3& b) {
	return vec3(b.getx() * a, b.gety() * a, b.getz() * a);
}

using colour = vec3;