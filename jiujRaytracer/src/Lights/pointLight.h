#pragma once
#include "../core.h"

class pointLight
{
public:
	pointLight();
	pointLight(point3 p, colour c);
	point3 getPosition();
	colour getColour();

private:
	point3 pos;
	colour col;

};

