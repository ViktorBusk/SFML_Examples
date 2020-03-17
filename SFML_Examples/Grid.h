#pragma once
#include "Node.h"

using namespace sf;

class Grid
{
private:
	void init();

public:
	Vector2i gridWorldSize;
	Vector2i dimensions;
	Vector2f scale;
	Vector2i start;
	Vector2i end;
	static bool pathFound;
	
	std::vector<std::vector<Node>> grid;
	std::vector<Node> path;

	Grid(RenderWindow &window, Vector2i gridWorldSize, Vector2i dimensions);
	~Grid();

	//Accessors


	//Modifiers

	
	//Functions
	void clear();
	void AStar(bool visualize = false, RenderWindow* window = nullptr);
	void AStarFibb(bool visualize = false, RenderWindow* window = nullptr);
	void retracePath(Node *startNode, Node *endNode);
	const std::vector<Node*> getNeighbours(const Node *node);
	void draw(RenderWindow &window);
	static void zoomViewAt(Vector2i pixel, RenderWindow& window, float zoom);
	static void pollEvents(RenderWindow &window);

	//Utilities
	struct mouse
	{
		Vector2f pos = Vector2f(0, 0);
		Vector2f pPos = pos;
		Vector2f startPoint = Vector2f(0, 0);
		bool left = false;
		bool right = false;
		bool holding = false;
		float radius = 1;
		bool push = false;

		void update(RenderWindow &window)
		{
			this->pos = Vector2f(window.mapPixelToCoords(Mouse::getPosition(window)));
			this->left = Mouse::isButtonPressed(Mouse::Button::Left);;
			this->right = Mouse::isButtonPressed(Mouse::Button::Right);

			if (this->right)
			{
				
			}
		}
		template <typename T>
		static bool rectColision(T obj, mouse m)
		{
			if (obj.getPosition().x < m.pos.x + 1 &&
				obj.getPosition().x + obj.getGlobalBounds().width > m.pos.x &&
				obj.getPosition().y < m.pos.y + 1 &&
				obj.getPosition().y + obj.getGlobalBounds().height > m.pos.y) {
				return true;
			}
			else
			{
				return false;
			}
		}
	};
};

