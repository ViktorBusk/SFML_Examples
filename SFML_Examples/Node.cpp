#include "Node.h"

Node::Node(Vector2f worldPosition, bool walkable)
{
	this->walkable = walkable;
	this->worldPosition = worldPosition;
	this->isInOpen = false;
	this->isInClosed = false;
	this->isInPath = false;
}

Node::~Node()
{

}

void Node::draw(RenderWindow &window, const Color &color, const Vector2f &scale)
{
	RectangleShape square;
	square.setPosition(Vector2f(this->worldPosition.x*scale.x,
								this->worldPosition.y*scale.y));
	square.setSize(scale);
	square.setFillColor(color);
	square.setOutlineColor(Color::Black);
	square.setOutlineThickness(scale.x/10);
	
	window.draw(square);
}

void Node::reset()
{
	this->g = 0;
	this->h = 0;
	this->isInPath = false;
	this->isInOpen = false;
	this->isInClosed = false;
	this->parent = nullptr;
}

unsigned const int Node::heuristic(const Node &current, const Node &destination)
{
	int dx = abs(current.worldPosition.x - destination.worldPosition.x);
	int dy = abs(current.worldPosition.y - destination.worldPosition.y);

	////Manhattan distance
	//return D1 * (dx + dy);

	//Diagonal distance (Patrick Lesters method)
	if (dx > dy) return D2 * dy + D1 * (dx - dy);
	return D2 * dx + D1 * (dy - dx);
	
	////Euclidean distance
	//return D1 * (dx * dx + dy * dy);
}

//Octile distance
int Node::D1 = 10;
int Node::D2 = 10*sqrt(2);
