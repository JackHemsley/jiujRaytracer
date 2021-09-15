#pragma once
#include "Mat4.h"
#include "../vec3.h"
#include "../Points/point3.h"
#include "../normal.h"

class Transform
{
public:
	Transform();
	Transform(Mat4 m);

	static Transform Translate(double x, double y, double z) { return Transform(Mat4(1, 0, 0, x, 0, 1, 0, y, 0, 0, 1, z, 0, 0, 0, 1)); }
	static Transform Scale(double x, double y, double z) { return Transform(Mat4(x, 0, 0, 0, 0, y, 0, 0, 0, 0, z, 0, 0, 0, 0, 1)); }
	static Transform RotateX(double theta) { 
		double cosTheta = cos(theta);
		double sinTheta = sin(theta);
		return Transform(Mat4(1, 0, 0, 0, 0, cosTheta, -sinTheta, 0, 0, sinTheta, cosTheta, 0, 0, 0, 0, 1));
	};;
	static Transform RotateY(double theta) {
		double cosTheta = cos(theta);
		double sinTheta = sin(theta);
		return Transform(Mat4(cosTheta, 0, sinTheta, 0, 0, 1, 0, 0, -sinTheta, 0, cosTheta, 0, 0, 0, 0, 1));
	}
	static Transform RotateZ(double theta){
		double cosTheta = cos(theta);
		double sinTheta = sin(theta);
		return Transform(Mat4(cosTheta, -sinTheta, 0, 0, sinTheta, cosTheta, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1));
	}
	static Transform Shear(double xy, double xz, double yx, double yz, double zx, double zy ) {
		return Transform(Mat4(1, xy, xz, 0, yx, 1, yz, 0, zx, zy, 1, 0, 0, 0, 0, 1));
	}

	const Mat4 getMat() const;
	const Mat4 getMatInv() const;

	Transform operator*(const Transform& other);
	const Transform operator*(const Transform& other) const;
	vec3 operator*(const vec3& other);
	const vec3 operator*(const vec3& other) const; 
	point3 operator*(const point3& other);
	const point3 operator*(const point3& other) const;
	normal operator*(const normal& other);
	const normal operator*(const normal& other) const;
	ray operator*(const ray& other);
	const ray operator*(const ray& other) const;


private:
	Mat4 m;
	Mat4 mInv;

};

