#pragma once
#include "Shape.h"
#include "../core.h"
class Sphere : public Shape
{
public:
	Sphere();
	Sphere(const double radius);
	Sphere(Transform ObjectToWorld, Material m, const double radius);

	bool intersect(const ray& r, double t_min, double t_max,  hit_record& rec);
	normal normal_at(point3 p);

private:
	double radius;


};

