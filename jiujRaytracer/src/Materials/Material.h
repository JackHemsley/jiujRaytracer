#pragma once
#include "../Util/vec3.h"
class Material
{
public:
	Material();
	Material(double ambient, double diffuse, double specular, double shininess, colour c);

	double getAmbient();
	double getDiffuse();
	double getSpecular();
	double getShininess();
	colour getColour();

private:
	colour c;
	double ambient;
	double diffuse;
	double specular;
	double shininess;
};

