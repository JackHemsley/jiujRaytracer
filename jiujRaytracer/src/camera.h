#pragma once
#include "core.h"

class camera
{
public:
	camera();
	camera(point3 origin, double h_image_size, double v_image_size, double fov);
	camera(point3 origin, point3 lookat, vec3 up, double h_image_size, double v_image_size, double fov);
	camera(double h_image_size, double v_image_size, double fov);
	Transform view_transform(point3 origin, point3 lookat, vec3 up);
	ray shootRay(double x, double y);



public:
	
	void calculate_canvas_dimentions(double h_size, double v_size, double fov);

	Transform t;
	int h_image_size;
	int v_image_size;
	double half_canvas_width;
	double half_canvas_height;
	double pixel_size;
	double fov;

};

