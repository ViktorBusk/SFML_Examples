#include "Predator.h"


Predator::Predator(Vector2f pos, Vector2f vel) :
	Boid(pos, vel)
{
	this->shape.setOrigin(0, 0);
	this->shape.setScale(this->shape.getScale().x * 2, this->shape.getScale().y * 2);
	this->shape.setOrigin(this->shape.getLocalBounds().width / 2, this->shape.getLocalBounds().height / 2);
	this->shape.setFillColor(Color(255, 0, 0));
}

Predator::~Predator()
{
}

void Predator::update(std::vector<Boid>& boids)
{
	Vector2f v3;
	Vector2f pc;
	unsigned int flockCount = 0;
	
	for (auto &boid : boids)
	{
		if (distance(boid) < Boid::perception*2)
		{
			pc += boid.getPos();
			flockCount++;
		}
	}

	//3: Cohesion
	v3 = this->rule3(pc, flockCount);

	this->vel = this->vel + Vector2f(v3.x, v3.y);

	this->speedLimit(Boid::vlim*1.1);
	this->directionRotate();
	this->shape.move(this->vel);
}

