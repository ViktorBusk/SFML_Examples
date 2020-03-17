#ifndef BOID
#define BOID

#include "utils.hpp"

using namespace sf;

class Boid
{
private:
	Vector2f rule1(Vector2f &c);
	Vector2f rule2(Vector2f &pv, unsigned int &flockCount);
	
protected:
	static float const size;
	static float const vlim;
	CircleShape shape;
	Vector2f vel;
	void speedLimit(const float &limit);
	void directionRotate();
	inline const float distance(const Boid &other) { return sqrt(pow((this->getPos().x - other.getPos().x), 2) + pow((this->getPos().y - other.getPos().y), 2)); }
	Vector2f rule3(Vector2f &pc, unsigned int &flockCount);

public:
	//Rule factors
	static float perception;
	static float scared;
	static float factor1;
	static float factor2;
	static float factor3;
	bool alive;

	//Constructors
	Boid(Vector2f pos, Vector2f vel);
	virtual ~Boid();

	//Accessors
	inline const Vector2f getPos() const { return this->shape.getPosition(); }
	inline const Vector2f getVel() const { return this->vel; }
	inline const float getRadius() const { return this->shape.getRadius(); }
	//Modifiers
	virtual void update(std::vector<Boid> &boids);
	void draw(RenderWindow &window);
	inline void addVel(Vector2f vel) { this->vel += vel; }
};

#endif