#include "Sphere.h"

Sphere::Sphere() : radius(1) {};
Sphere::Sphere( const double radius) : radius(radius) {};
Sphere::Sphere(Transform ObjectToWorld, Material m, const double radius) : Shape(ObjectToWorld, m), radius(radius) {};

bool Sphere::intersect(const ray& r, double t_min, double t_max, hit_record& hit_rec){

	//First Transform Ray to Object Space by using inverse Transform of Object to World Space

	ray rObj = this->getTransform().getMatInv() * r;
	//Calculate if Sphere is hit by ray or not
	vec3 sphere_to_ray = rObj.getOrigin() - point3(0,0,0);
	double a = rObj.getDirection().dot(rObj.getDirection());
	double b = 2 * rObj.getDirection().dot(sphere_to_ray);
	double c = sphere_to_ray.dot(sphere_to_ray) - 1;
	double disc = b * b - 4 * a * c;

	if (disc < 0) {
		return false;
	}

	hit_rec.t_close = (-b - sqrt(disc)) / (2 * a);
	hit_rec.t_far = (-b + sqrt(disc)) / (2 * a);
	hit_rec.t = hit_rec.t_close;
	if (hit_rec.t_close < t_min || hit_rec.t_close > t_max) {
		hit_rec.t = hit_rec.t_far;
		if (hit_rec.t_far > t_max) {
			return false;
		}
	}

	hit_rec.p =  point3(r.getOrigin() + r.getDirection() * hit_rec.t_close);
	hit_rec.hit_normal = normal_at(hit_rec.p);
	hit_rec.m = this->getMaterial();
	return true;
}

normal Sphere::normal_at(point3 p) {

	point3 object_point = this->getTransform().getMatInv() * p;
	normal object_normal = normal(object_point - point3(0, 0, 0));
	normal world_normal = this->getTransform() * object_normal;
	return world_normal.normalise();

}