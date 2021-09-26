#pragma once
#include "../core.h"
#include "../ray.h"
#include "../Materials/Material.h"
#include <vector>

struct hit_record{

	Material m = Material();
	double t = 0;
	double t_close = 0;
	double t_far = 0;
	normal hit_normal = normal();
	vec3 v;
	point3 p = point3();
	bool inside = false;

};


class Shape
{

public:
	Shape();
	Shape(Transform ObjectToWorld, Material m);
	virtual ~Shape() {};

	virtual bool intersect(const ray& r, double t_min, double t_max, hit_record& hit_rec) = 0;
	void setTransform(Transform t);
	void setMaterial(Material mat);
	Transform getTransform();
	Material getMaterial();
	void updateTransform(Transform t);

private:
	//Instead of Transforming Shape from object to world space transform ray from world to object space by applying inverse transform
	//When a sphere is transformed create a new Sphere containing transform
	Transform ObjectToWorld;
	Material m;

};

