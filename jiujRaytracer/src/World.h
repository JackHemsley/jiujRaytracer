#pragma once
#include <vector>
#include <set>
#include "Lights/pointLight.h"
#include "core.h"


struct intersection {
	std::shared_ptr<Shape> object;
	double t;

	intersection(std::shared_ptr<Shape> object, double t) : object(object), t(t) {}
	bool operator< (const intersection right) const
	{
		return t < right.t;
	}
};


class World
{
public:

	World();
	World(std::vector<std::shared_ptr<Shape>> shapeList, std::vector<std::shared_ptr<pointLight>> lights);

	void addShape(std::shared_ptr<Shape> s);
	bool intersect(const ray& r, double t_min, double t_max, hit_record& hit_rec, std::set<intersection>& intersections);


private:
	std::vector<std::shared_ptr<Shape>> shapeList;
	std::vector<std::shared_ptr<pointLight>> lights;


};

