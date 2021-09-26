#include <iostream>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>

#include "Shapes/Sphere.h"
#include "Shapes/Shape.h"
#include "core.h"
#include "Util/Matrices/Transform.h"
#include "Lights/pointLight.h"
#include "World.h"
#include "camera.h"


namespace vec {
	vec3 reflect(const vec3& v, const normal& n) {
		vec3 v2 = n.normalToVec3();
		return v - v2 * 2 * v.dot(v2);
		
	}
}

bool is_shadowed(const World& w, pointLight light, point3 p) {

	hit_record rec = hit_record();
	std::set<intersection> intersections;
	vec3 v = light.getPosition() - p;
	double distance = v.length();
	vec3 dir = v.normalise();
	ray r = ray(p, dir);
	if (w.intersect(r, 0.001, 1000, rec, intersections)) {
		if (rec.t < distance) {
			return true;
		}
	}
	return false;

}

colour lighting_at(Material m, pointLight light, point3 point_hit, vec3 view_dir, normal surface_norm, bool in_shadow) {
	colour effective_colour = m.getColour() * light.getColour();
	vec3 light_vector = (light.getPosition() - point_hit).normalise();

	colour ambient_colour = m.getAmbient() * effective_colour;
	
	if (in_shadow) {
		return ambient_colour;
	}

	double light_dot_normal = light_vector.dot(surface_norm.normalToVec3());

	double reflect_dot_eye = 0;
	if (light_dot_normal <= 0) {
		return(ambient_colour);
	}
	else {
		colour diffuse_colour = effective_colour * m.getDiffuse() * light_dot_normal;
		vec3 negv = (-1 * light_vector);
		vec3 reflectv = vec::reflect(negv, surface_norm);
		reflect_dot_eye = reflectv.dot(view_dir);
		if (reflect_dot_eye < 0) {
			return(ambient_colour + diffuse_colour);
		}
		double factor = std::pow(reflect_dot_eye, m.getShininess());
		colour specular_colour = light.getColour() * m.getSpecular() * factor;

		return ambient_colour + diffuse_colour + specular_colour;
	}
}


void render(std::vector<std::vector<colour>>& canvas, const World& world, camera cam, pointLight light) {
	
	hit_record rec;
	std::set<intersection> intersections;
	for (int i = 0; i < canvas.size(); i++) {
		for (int j = 0; j < canvas[0].size(); j++) {
			ray r = cam.shootRay(i, j);
			if (world.intersect(r, 0.001, 1000, rec, intersections)) {
				Material m = rec.m;
				point3 point_hit = rec.p;
				vec3 view_dir = -1 * r.getDirection();
				normal surface_norm = rec.hit_normal;
				colour c = lighting_at(m, light, point_hit, view_dir, surface_norm, false);
				canvas[i][j] = c;
			}
		}
	}
}

int main() {
	
	const double pi = 3.14159265358979323846;

	std::ofstream imageFile;
	imageFile.open("image.ppm");
	
	std::cout << "hi" << std::endl;

	const int canvas_height = 150;
	const auto aspect_ratio = 16.0/9.0;
	const int canvas_width = 150;
	double fov = pi / 3;


	camera c = camera(canvas_width, canvas_height, fov);
	c.view_transform(point3(0, 1.5, -5), point3(0, 1, 0), vec3(0, 1, 0));

	const int low = 0;
	const int high = 255;
	std::vector<std::vector<colour>> canvas(canvas_height, std::vector<colour>(canvas_width, 0));
 	
	imageFile << ("P3\n") << canvas_width << (" ") << canvas_height << ("\n") << ("255") << std::endl;
	
	Sphere s = Sphere();
	s.setTransform(Transform::Translate(0, 0, 10));
	s.setMaterial(Material(0.1, 0.9, 0.9, 200, colour(1, 0.2, 1)));

	pointLight light = pointLight(point3(-10, 10, -10), colour(1, 1, 1));
	
	
	Sphere floor = Sphere();
	floor.setTransform(Transform::Scale(10, 0.01, 10));
	floor.setMaterial(Material(0.1, 0.9, 0, 200, colour(1, 0.9, 0.9)));

	Sphere left_wall = Sphere();
	left_wall.setMaterial(Material(0.1, 0.9, 0, 200, colour(1, 0.9, 0.9)));
	left_wall.setTransform(Transform::Translate(0,0,5)*Transform::RotateY(-pi/4)* Transform::RotateX(pi/2) * Transform::Scale(10, 0.01, 10));

	Sphere right_wall = Sphere();
	right_wall.setMaterial(Material(0.1, 0.9, 0, 200, colour(1, 0.9, 0.9)));
	right_wall.setTransform(Transform::Translate(0, 0, 5) * Transform::RotateY(pi / 4) * Transform::RotateX(pi / 2) * Transform::Scale(10, 0.01, 10));
	
	Sphere middle = Sphere();
	middle.setTransform(Transform::Translate(-0.5, 1, 0.5));
	middle.setMaterial(Material(0.1, 0.7, 0.3, 200, colour(0.1, 1.0, 0.5)));

	Sphere right = Sphere();
	right.setTransform(Transform::Translate(1.5, 0.5, -0.5) * Transform::Scale(0.5, 0.5, 0.5));
	right.setMaterial(Material(0.1, 0.7, 0.3, 200, colour(0.5, 1.0, 0.1)));

	Sphere left = Sphere();
	left.setTransform(Transform::Translate(-1.5, 0.33, -0.75) * Transform::Scale(0.33, 0.33, 0.33));
	left.setMaterial(Material(0.1, 0.7, 0.3, 200, colour(1, 0.8, 0.1)));


	hit_record hit;
	World objects = World();
	
	objects.addShape(std::make_shared<Sphere>(floor));
	objects.addShape(std::make_shared<Sphere>(left_wall));
	objects.addShape(std::make_shared<Sphere>(right_wall));
	
	objects.addShape(std::make_shared<Sphere>(middle));
	objects.addShape(std::make_shared<Sphere>(right));
	objects.addShape(std::make_shared<Sphere>(left));

	



	
	std::set<intersection> intersections;

	#pragma omp parallel for
	for (auto y = 0; y < canvas_height; y++) {
		for (auto x = canvas_width - 1; x >= 0; x--) {
			ray r = c.shootRay(x, y);
			if (objects.intersect(r, 0.001, 1000, hit, intersections)) {
				bool shadowed = is_shadowed(objects, light, hit.p);
				Material m = hit.m;
				point3 point_hit = hit.p;
				vec3 view_dir = -1 * r.getDirection();
				normal surface_norm = hit.hit_normal;
				colour c = lighting_at(m, light, point_hit, view_dir, surface_norm, shadowed);
				canvas[y][(size_t)canvas_width - x - 1] = c;
			}
		}
	}

	#pragma omp parallel for
	for (auto y = 0; y < canvas_height; y++) {
		for (auto x = 0; x < canvas_width; x++) {
				
			int r = std::clamp(static_cast<int>(canvas[y][x][0] * 256), low, high);
			int g = std::clamp(static_cast<int>(canvas[y][x][1] * 256), low, high);
			int b = std::clamp(static_cast<int>(canvas[y][x][2] * 256), low, high);

			imageFile << r << " " << g << " " << b << ("\n");
		}
	}
	
	imageFile.close();
	
	

	
	/*
	pointLight light = pointLight(point3(-10, 10, -10), colour(1, 1, 1));
	point3 p = point3(-2, 2, -2);

	Sphere middle = Sphere();
	middle.setMaterial(Material(0.1, 0.7, 0.3, 200, colour(0.1, 1.0, 0.5)));

	Sphere right = Sphere();
	right.setTransform(Transform::Scale(0.5, 0.5, 0.5));
	right.setMaterial(Material(0.1, 0.7, 0.3, 200, colour(0.5, 1.0, 0.1)));


	hit_record hit;
	World objects = World();

	objects.addShape(std::make_shared<Sphere>(middle));
	objects.addShape(std::make_shared<Sphere>(right));




	bool s = is_shadowed(objects, light, p);
	*/
	return 0;

}