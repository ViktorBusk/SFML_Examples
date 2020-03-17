#pragma once
#include "utils.hpp"

using namespace sf;

class Node
{
private:
	static int D1;
	static int D2;

public:
	int g;
	int h;
	bool walkable;
	bool isInPath;
	bool isInOpen;
	bool isInClosed;

	Vector2f worldPosition;
	Node *parent;

	Node(Vector2f worldPosition=Vector2f(0.f, 0.f), bool walkable=true);
	~Node();

	//Accessors 
	const inline int get_f() const { return this->g + this->h; }
	
	//Modifiers

	//Operators

	//Funtions
	void draw(RenderWindow &window, const Color &color, const Vector2f &scale);
	void reset();

	static unsigned const int heuristic(const Node &current, const Node &destination);
};

