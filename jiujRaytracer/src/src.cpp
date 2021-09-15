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


namespace vec {
	vec3 reflect(const vec3& v, const normal& n) {
		vec3 v2 = n.normalToVec3();
		return v - v2 * 2 * v.dot(v2);
		
	}
}

colour lighting_at(Material m, pointLight light, point3 point_hit, vec3 view_dir, normal surface_norm) {
	colour effective_colour = m.getColour() * light.getColour();
	vec3 light_vector = (light.getPosition() - point_hit).normalise();

	colour ambient_colour = m.getAmbient() * effective_colour;
	
	double light_dot_normal = light_vector.dot(surface_norm.normalToVec3());

	double reflect_dot_eye = 0;
	if (light_dot_normal <= 0) {
		return(ambient_colour);
	}
	else {
		colour diffuse_colour = effective_colour * m.getDiffuse() * light_dot_normal;

		vec3 reflectv = vec::reflect(light_vector, surface_norm);
		reflect_dot_eye = reflectv.dot(-1 * view_dir);
		if (reflect_dot_eye < 0) {
			return(ambient_colour + diffuse_colour);
		}
		double factor = std::pow(reflect_dot_eye, m.getShininess());
		colour specular_colour = light.getColour() * m.getSpecular() * factor;

		return ambient_colour + diffuse_colour + specular_colour;
	}
}

int main() {

	const double pi = 3.14159265358979323846;

	std::ofstream imageFile;
	imageFile.open("image.ppm");

	const int canvas_height = 200;
	const auto aspect_ratio = 16.0/9.0;
	const int canvas_width = (int) (canvas_height * aspect_ratio);
	
	const int low = 0;
	const int high = 255;
	std::vector<std::vector<colour>> canvas(canvas_height, std::vector<colour>(canvas_width, 0));
 	
	imageFile << ("P3\n") << canvas_width << (" ") << canvas_height << ("\n") << ("255") << std::endl;
	float half_y = canvas_height / 2;
	float half_x = canvas_width / 2;
	point3 r_org = point3(0, 0, -10);
	Sphere s = Sphere();
	Sphere s2 = Sphere();
	s2.setTransform(Transform::Translate(1, 1, 15));
	s2.setMaterial(Material(0.1, 0.9, 0.9, 200, colour(0, 0, 1)));
	s.setTransform(Transform::Translate(0, 0, 10));
	s.setMaterial(Material(0.1, 0.9, 0.9, 200, colour(1, 0.2, 1)));
	pointLight light = pointLight(point3(-10, 10, -10), colour(1, 1, 1));
	
	hit_record hit;
	std::cout << "hi" << std::endl;
	World objects = World();
	objects.addShape(std::make_shared<Sphere>(s));
	objects.addShape(std::make_shared<Sphere>(s2));
	std::set<intersection> intersections;
	
	for (auto y = 0; y < canvas_height; y++) {
		float im_y = (half_y - y)/canvas_height;
		for (auto x = 0; x < canvas_width; x++) {
			double im_x = (-half_x + x)/canvas_width*aspect_ratio;
			ray r = ray(r_org, (point3(im_x, im_y, 0) - r_org).normalise());
			if (objects.intersect(r, 0.001, 1000, hit, intersections)) {
				Material m = hit.m;
				point3 point_hit = hit.p;
				vec3 view_dir = -1 * r.getDirection();
				normal surface_norm = hit.hit_normal;
				colour c = lighting_at(m, light, point_hit, view_dir, surface_norm);
				canvas[y][x] = c;
			}
		}
	}


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
	Material m = Material(0.1, 0.9, 0.9, 200, colour(1, 1, 1));
	pointLight l = pointLight(point3(0, 10, -10), colour(1, 1, 1));
	point3 point_hit = point3(0,0,0);
	//vec3 view_dir = vec3(0, -std::sqrt(2)/2.0, -std::sqrt(2) / 2.0);
	vec3 view_dir = vec3(0, 0, -1);
	normal surface_norm = normal(0, 0, -1);
	colour res = lighting_at(m, l, point_hit, view_dir, surface_norm);
	std::cout << res << std::endl;
	*/
	return 0;

}