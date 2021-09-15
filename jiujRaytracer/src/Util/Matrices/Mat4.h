#pragma once
#include <vector>
#include <iostream>
#include "../../ray.h"
#include "../vec3.h"
#include "../normal.h"
#include "../Points/point3.h"
#include <functional>

class Mat4 {

public:

	Mat4();
	Mat4(double number);
	Mat4(double m00, double m01, double m02, double m03,
		double m10, double m11, double m12, double m13,
		double m20, double m21, double m22, double m23,
		double m30, double m31, double m32, double m33);
	Mat4(std::vector<std::vector<double>> a);

	const std::vector<std::vector<double>>& getmat() const;
	Mat4 transpose() const;
	Mat4 inverse() const;

	friend std::ostream& operator<<(std::ostream& stream, const Mat4& m);
	double& operator()(const int x, const int y);
	const double operator()(const int x, const int y) const;
	Mat4 operator+(const Mat4& a);
	const Mat4 operator+(const Mat4& a) const;
	Mat4 operator-(const Mat4& a);
	const Mat4 operator-(const Mat4& a) const;
	bool operator ==(const Mat4& a);
	const bool operator ==(const Mat4& a) const;
	Mat4 operator *(const Mat4& a);
	const Mat4 operator *(const Mat4& a) const;
	vec3 operator *(const vec3& a);
	const vec3 operator *(const vec3& a) const;
	point3 operator *(const point3& a);
	const point3 operator *(const point3& a) const;
	ray operator* (const ray& a);
	const ray operator* (const ray& a) const;
	Mat4 operator *(const double a);
	const Mat4 operator *(const double a) const;
	Mat4 operator /(const double a);
	const Mat4 operator /(const double a) const;


private:
	std::vector<std::vector<double>> mat;

};
inline
std::ostream& operator <<(std::ostream& stream, Mat4& m) {
	for (auto x : m.getmat()) {
		for (auto y : x) {
			stream << y << " ";
		}
		stream << ("\n");
	}
	return stream;
}

