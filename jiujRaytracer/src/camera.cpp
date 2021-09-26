#include "camera.h"

void camera::calculate_canvas_dimentions(double h_image_size, double v_image_size, double fov) {

	double half_view = tan(fov / 2);
	double aspect_ratio = h_image_size / v_image_size;
	if (aspect_ratio >= 1.0) {
		half_canvas_width = half_view;
		half_canvas_height = half_view / aspect_ratio;
	}
	else {
		half_canvas_height = half_view;
		half_canvas_width = half_view * aspect_ratio;
	}
	pixel_size = (half_canvas_width * 2) / h_image_size;

}

camera::camera() : t(), h_image_size(640), v_image_size(480), fov(3.14/2) {
	t = Transform(Mat4());
	calculate_canvas_dimentions(h_image_size, v_image_size, fov);
}

camera::camera(double h_image_size, double v_image_size, double fov) : t(), h_image_size(h_image_size), v_image_size(v_image_size), fov(fov) {
	t = Transform(Mat4());
	calculate_canvas_dimentions(h_image_size, v_image_size, fov);
}

camera::camera(point3 origin, double h_image_size, double v_image_size, double fov) : t(),  h_image_size(h_image_size), v_image_size(v_image_size),  fov(fov){
	view_transform(origin, point3(0, 0, 0), vec3(0, 1, 0)); 
	calculate_canvas_dimentions(h_image_size, v_image_size, fov);
}

camera::camera(point3 origin, point3 lookat, vec3 up, double h_image_size, double v_image_size, double fov) : t(), h_image_size(h_image_size), v_image_size(v_image_size), fov(fov) {
	view_transform(origin, lookat, up);
	calculate_canvas_dimentions(h_image_size, v_image_size, fov);
}

Transform camera::view_transform(point3 origin, point3 lookat, vec3 up) {

	vec3 dir = (lookat - origin).normalise();
	vec3 upNormal = up.normalise();
	vec3 left = dir.cross(upNormal);
	vec3 trueUp = left.cross(dir);

	Mat4 orientation = Mat4(left.getx(), left.gety(), left.getz(), 0.0,
		trueUp.getx(), trueUp.gety(), trueUp.getz(), 0.0,
		- dir.getx(), -dir.gety(), -dir.getz(), 0.0,
		0.0, 0.0, 0.0, 1.0);

	orientation = orientation * Transform::Translate(-origin.getx(), -origin.gety(), -origin.getz()).getMat();
	t = Transform(orientation);

	
	return t;

}

ray camera::shootRay(double x, double y) {

	double xOffset = (x + 0.5) * pixel_size;
	double yOffset = (y + 0.5) * pixel_size;
	
	double adjusted_x = half_canvas_width - xOffset;
	double adjusted_y = half_canvas_height - yOffset;

	point3 pix = t.getMatInv() * point3(adjusted_x, adjusted_y, -1);
	point3 camera_origin = t.getMatInv() * point3(0, 0, 0);
	vec3 ray_dir = (pix - camera_origin).normalise();

	return ray(camera_origin, ray_dir);

}