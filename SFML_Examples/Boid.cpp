#include "Boid.h"

Boid::Boid(Vector2f pos, Vector2f vel)
{
	this->vel = vel;
	this->shape = CircleShape(this->size, 3);
	this->shape.setScale(Vector2f(0.7, 1));
	this->shape.setOrigin(this->shape.getLocalBounds().width / 2, this->shape.getLocalBounds().height / 2);
	this->directionRotate();
	this->shape.setPosition(pos);
	this->alive = true;
}

Boid::~Boid()
{

}

Vector2f Boid::rule1(Vector2f &c)
{
	return Vector2f(c.x*factor1, c.y*factor1);
}
Vector2f Boid::rule2(Vector2f &pv, unsigned int &flockCount)
{
	if (flockCount == 0) flockCount = 1;
	pv = Vector2f(pv.x / flockCount, pv.y / flockCount);
	return Vector2f((pv.x - this->vel.x)*factor2, (pv.y - this->vel.y)*factor2);
}
Vector2f Boid::rule3(Vector2f &pc, unsigned int &flockCount)
{
	if (flockCount == 0) flockCount = 1;
	pc = Vector2f(pc.x / flockCount, pc.y / flockCount);
	Vector2f vec = (pc - this->getPos());
	return Vector2f(vec.x / 100*factor3, vec.y/100*factor3);
}

void Boid::directionRotate()
{
	float dx = this->vel.x*INT_MAX - this->getPos().x;
	float dy = this->vel.y*INT_MAX - this->getPos().y;
	
	float rotation = (atan2(dy, dx)) * 180 / PI + 90;
	this->shape.setRotation(rotation);
}

void Boid::speedLimit(const float &limit)
{
	if (abs(this->vel.x) > limit)
	{
		this->vel.x = this->vel.x / abs(this->vel.x) * limit;
	}

	if (abs(this->vel.y) > limit)
	{
		this->vel.y = this->vel.y / abs(this->vel.y) * limit;
	}
}

void Boid::draw(RenderWindow &window)
{
	window.draw(this->shape);
}

void Boid::update(std::vector<Boid>& boids)
{
	Vector2f v1, v2, v3;
	
	Vector2f pc;
	Vector2f c(0.f, 0.f);
	Vector2f pv;
	unsigned int flockCount = 0;

	for (auto &boid : boids)
	{
		if (&boid == this) continue;
		if (distance(boid) < Boid::perception)
		{
			pc += boid.getPos();
			pv += boid.getVel();
			
			if (distance(boid) < 2.5 * Boid::size) {
				c = c - (boid.getPos() - this->getPos());
				c = Vector2f(c.x / distance(boid), c.y / distance(boid));
			}
			flockCount++;
		}
	}
	//1: Seperation
	v1 = this->rule1(c);
	//2: Alignment
	v2 = this->rule2(pv, flockCount);
	//3: Cohesion
	v3 = this->rule3(pc, flockCount);

	this->vel = this->vel + v1 + v2 + v3;

	this->speedLimit(Boid::vlim);
	this->directionRotate();
	this->shape.move(this->vel);

}

//Constants
float const Boid::size = 5;
float const Boid::vlim = 0.5;

//Adjustbles
float Boid::perception = 500;
float Boid::scared = Boid::factor1/2;
float Boid::factor1 = 0.1/2;
float Boid::factor2 = 0.01/2;
float Boid::factor3 = 0.01/2;