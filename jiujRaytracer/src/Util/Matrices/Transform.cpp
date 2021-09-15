#include "Transform.h"

Transform::Transform() {};
Transform::Transform(Mat4 m) : m(m) { mInv = m.inverse(); };

const Mat4 Transform::getMat() const {
	return m;
}

const Mat4 Transform::getMatInv() const {
	return mInv;
}

Transform Transform::operator*(const Transform& other) {
		return Transform(m * other.getMat());
}

const Transform Transform::operator*(const Transform& other) const{
	return Transform(m * other.getMat());
}

vec3 Transform::operator*(const vec3& other) {
	return m * other;
}

const vec3 Transform::operator*(const vec3& other) const {
	return m * other;
}

point3 Transform::operator*(const point3& other) {
	return m * other;
}
const point3 Transform::operator*(const point3& other) const {
	return m * other;
}

normal Transform::operator*(const normal& other) {
	return normal(mInv(0, 0) * other.getx() + mInv(1, 0) * other.gety() + mInv(2, 0) * other.getz(),
		mInv(0, 1) * other.getx() + mInv(1, 1) * other.gety() + mInv(2, 1) * other.getz(),
		mInv(0, 2) * other.getx() + mInv(1, 2) * other.gety() + mInv(2, 2) * other.getz());
}

const normal Transform::operator*(const normal& other) const {
	return normal(mInv(0, 0) * other.getx() + mInv(1, 0) * other.gety() + mInv(2, 0) * other.getz(),
		mInv(0, 1) * other.getx() + mInv(1, 1) * other.gety() + mInv(2, 1) * other.getz(),
		mInv(0, 2) * other.getx() + mInv(1, 2) * other.gety() + mInv(2, 2) * other.getz());
}

ray Transform::operator*(const ray& other) {
	return m * other;
}
const ray Transform::operator*(const ray& other) const {
	return m * other;
}