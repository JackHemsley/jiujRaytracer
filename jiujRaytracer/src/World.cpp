#include "World.h"

World::World() : shapeList(std::vector<std::shared_ptr<Shape>>()), lights(std::vector<std::shared_ptr<pointLight>>()) {};
World::World(std::vector<std::shared_ptr<Shape>> shapeList, std::vector<std::shared_ptr<pointLight>> lights) : shapeList(shapeList), lights(lights){};

void World::addShape(std::shared_ptr<Shape> s) {
	shapeList.push_back(s);
}

bool World::intersect(const ray& r, double t_min, double t_max, hit_record& hit_rec, std::set<intersection>& intersections) const {


	bool anything_hit = false;
	hit_record best_hit = hit_rec;
	double min_hit = t_max + 1;

	for (const auto& s : shapeList) {
		
		if (s->intersect(r, t_min, t_max, hit_rec)) {
			if (hit_rec.t < min_hit) {
				min_hit = hit_rec.t;
				best_hit = hit_rec;
			}
			anything_hit = true;
			intersections.insert(intersection(s, hit_rec.t_close));
			intersections.insert(intersection(s, hit_rec.t_far));
		}
	}

	hit_rec = best_hit;
	return anything_hit;
}

