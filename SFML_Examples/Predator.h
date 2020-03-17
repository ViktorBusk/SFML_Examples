#pragma once
#include "Boid.h"
class Predator : public Boid
{
public:
	Predator(Vector2f pos, Vector2f vel);
	virtual ~Predator();

	virtual void update(std::vector<Boid> &boids);
};



