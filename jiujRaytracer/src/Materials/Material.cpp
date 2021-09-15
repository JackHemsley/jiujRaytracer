#include "Material.h"
Material::Material() : ambient(0.1), diffuse(0.9), specular(0.9), shininess(200), c(colour(1,1,1)) {}
Material::Material(double ambient, double diffuse, double specular, double shininess, colour c) : ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess), c(c) {}

double Material::getAmbient() {
	return ambient;
}
double Material::getDiffuse() {
	return diffuse;
}
double Material::getSpecular() {
	return specular;
}
double Material::getShininess() {
	return shininess;
}

colour Material::getColour() {
	return c;
}