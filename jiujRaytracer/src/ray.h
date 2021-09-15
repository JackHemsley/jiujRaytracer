#pragma once
#include "Util/vec3.h"
#include "Util/Points/point3.h"

class ray
{
public:
	ray(point3 o, vec3 dir);
	point3 position(double t) const;
	point3 getOrigin() const;
	vec3 getDirection() const;
	friend std::ostream& operator<<(std::ostream& stream, const ray& m);

private:
	point3 origin;
	vec3 dir;
};

inline
std::ostream& operator <<(std::ostream& stream, ray& m) {
	stream << "Ray Origin";
	stream << "x: " << m.getOrigin().getx() << " y: " << m.getOrigin().gety() << " z: " << m.getOrigin().getz() << "\n";
	stream << "Ray Direction";
	stream << "x: " << m.getDirection().getx() << " y: " << m.getDirection().gety() << " z: " << m.getDirection().getz();
	
	return stream;
}
