#include "Shape.h"
Shape::Shape() {}
Shape::Shape(Transform ObjectToWorld, Material m) : ObjectToWorld(ObjectToWorld), m(m) {}

void Shape::setTransform(Transform t) { 
	ObjectToWorld = t;
}

void Shape::updateTransform(Transform t) {
	ObjectToWorld = ObjectToWorld * t;
}

void Shape::setMaterial(Material mat) {
	m = mat;
}

Material Shape::getMaterial() {
	return m;
}

Transform Shape::getTransform() {
	return ObjectToWorld;
}


