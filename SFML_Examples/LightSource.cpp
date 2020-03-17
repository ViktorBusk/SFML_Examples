#include "LightSource.h"

LightSource::LightSource()
{
	this->radius = 10000.f;
	this->lightAngle = 90 * PI / 180;
	this->shape.setRadius(15.f);
	this->moveAngle = 0;
	this->shape.setOrigin(this->shape.getLocalBounds().width / 2, this->shape.getLocalBounds().height / 2);
	this->spawnPos = Vector2f(rand() % WINDOWSIZE.x + 1, rand() % WINDOWSIZE.y + 1);
	this->shape.setPosition(spawnPos);
	this->shape.setFillColor(Color::Yellow);
}

LightSource::~LightSource()
{

}

bool LightSource::Ray::getLineIntersection(float p0_x, float p0_y, float p1_x, float p1_y, float p2_x, float p2_y, float p3_x, float p3_y, float * i_x, float * i_y)
{
	float s1_x, s1_y, s2_x, s2_y;
	s1_x = p1_x - p0_x;     s1_y = p1_y - p0_y;
	s2_x = p3_x - p2_x;     s2_y = p3_y - p2_y;

	float s, t;
	s = (-s1_y * (p0_x - p2_x) + s1_x * (p0_y - p2_y)) / (-s2_x * s1_y + s1_x * s2_y);
	t = (s2_x * (p0_y - p2_y) - s2_y * (p0_x - p2_x)) / (-s2_x * s1_y + s1_x * s2_y);

	if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
	{
		// Collision detected
		if (i_x != NULL)
			*i_x = p0_x + (t * s1_x);
		if (i_y != NULL)
			*i_y = p0_y + (t * s1_y);
		return 1;
	}

	return 0; // No collision
}

void LightSource::Ray::findClosestIntersectPoint(std::vector<Shape*> &polygons)
{
	float minDist = float(INT_MAX);
	Vector2f closestIntersectPoint(this->sourcePoint.x + cos(this->angle) * this->radius, this->sourcePoint.y + sin(this->angle) * this->radius);

	//Find the closest wall the ray intersects with and save the intersect point
	for (Shape* polygon : polygons)
	{
		for (size_t k = 0; k < polygon->getPointCount(); k++)
		{
			Vector2f polygonP1 = polygon->getPoint(k) + polygon->getPosition();
			Vector2f polygonP2;
			Vector2f currentIntersectPoint;

			//when on the last vertex connect it to the first one
			if (k < polygon->getPointCount() - 1) polygonP2 = polygon->getPosition() + polygon->getPoint(k + 1);
			else polygonP2 = polygon->getPosition() + polygon->getPoint(0);

			if (getLineIntersection(this->sourcePoint.x, this->sourcePoint.y,
				closestIntersectPoint.x, closestIntersectPoint.y,
				polygonP1.x, polygonP1.y,
				polygonP2.x, polygonP2.y,
				&currentIntersectPoint.x, &currentIntersectPoint.y))
			{
				float currentDist = Utils::distance(this->sourcePoint, currentIntersectPoint);
				if (currentDist < minDist)
				{
					minDist = currentDist;
					closestIntersectPoint = currentIntersectPoint;
				}
			}
		}
	}
	this->interSectPoint = closestIntersectPoint;
}

void LightSource::draw(RenderWindow * window, std::vector<Shape*> &polygons)
{
	Vector2f sourcePos = this->shape.getPosition();
	//Cast a ray to each vertex of all the polygons 
	for (Shape* polygon : polygons)
	{
		for (size_t i = 0; i < polygon->getPointCount(); i++)
		{
			Vector2f vertexPos = polygon->getPoint(i) + polygon->getPosition();
			float baseAngle = atan2f(vertexPos.y - sourcePos.y, vertexPos.x - sourcePos.x);
			float angle = 0;
			for (size_t j = 0; j < 2; j++)
			{
				if (j == 0) angle = baseAngle + 0.0001f;
				if (j == 1) angle = baseAngle - 0.0001f;

				Ray ray(sourcePos, angle);
				ray.findClosestIntersectPoint(polygons);
				this->rays.push_back(ray);
			}
		}
	}

	//sort IP based on angle to the LS
	std::sort(this->rays.begin(), this->rays.end(), [sourcePos](Ray &r1, Ray &r2) {
		return r1.angle < r2.angle;
	});

	Ray* rayP = this->rays.data();
	for (size_t i = 0; i < this->rays.size(); i++)
	{		
		Ray* currentRay = &rayP[i];
		Ray* nextRay;

		if (i < this->rays.size() - 1) nextRay = &rayP[i+1];
		else nextRay = &rayP[0];

		ConvexShape triangleSegment;
		triangleSegment.setPointCount(3);
		triangleSegment.setPoint(0, sourcePos);
		triangleSegment.setPoint(1, currentRay->interSectPoint);
		triangleSegment.setPoint(2, nextRay->interSectPoint);
		triangleSegment.setFillColor(Color(255, 134, 124, 100));
		window->draw(triangleSegment);
	}

	//for every ray Connect 2 adjacent rays and a wall to make a triangle and then draw it 

	//Draw lightSource
	this->mousePos = window->mapPixelToCoords(Mouse::getPosition(*window), window->getView());
	window->draw(this->shape);
	this->rays.clear();
}

void LightSource::update(const float & dt)
{
	//this->moveAngle += 5*dt;
	//this->shape.setPosition(this->spawnPos.x + 50*cos(moveAngle), this->spawnPos.y + 50*sin(moveAngle));
	if (!this->holding &&
		Mouse::isButtonPressed(Mouse::Left) &&
		Utils::distance(Vector2f(this->mousePos), this->shape.getPosition()) < this->shape.getRadius())
	{
		this->holding = true;
		this->follow = true;
	}
	else if (this->follow) this->shape.setPosition(Vector2f(this->mousePos));

	if (!Mouse::isButtonPressed(Mouse::Left)) this->holding = false, this->follow = false;
}

Vector2f LightSource::mousePos = Vector2f(0, 0);
bool LightSource::holding = false;
