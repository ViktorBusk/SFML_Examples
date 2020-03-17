#include "Grid.h"
#include "Fibonacci.hpp"
#include <ctime>

void Grid::init()
{
	//Always generate a possile path
	while (!Grid::pathFound)
	{
		this->grid.clear();
		//Push nodes into the 2D-array
		for (int x = 0; x < this->dimensions.x; x++)
		{
			std::vector<Node>temp;
			for (int y = 0; y < this->dimensions.y; y++)
			{
				temp.push_back(Node(Vector2f(x, y), rand() % 2));
			}
			this->grid.push_back(temp);
		}

		//Make the startPoint and endpoint random in the grid
		this->start = Vector2i(0, 0);

		this->end = Vector2i(this->dimensions.x - 1, this->dimensions.y - 1);

		//Mame sure the start and end is not the same node in the grid
		while (this->start == this->end)
		{
			this->end = Vector2i(rand() % this->dimensions.x, rand() % this->dimensions.y);
		}
		//Run the A-star without visualising it
		this->AStarFibb();
	}
	//Clear old data from the previous A* run
	this->clear();
}

void Grid::clear()
{
	Grid::pathFound = false;

	for (int x = 0; x < this->dimensions.x; x++)
	{
		for (int y = 0; y < this->dimensions.y; y++)
		{
			Node* currentNode = &this->grid[x][y];
			currentNode->reset();
		}
	}
}

Grid::Grid(RenderWindow &window, Vector2i gridWorldSize, Vector2i dimensions)
{
	this->gridWorldSize = gridWorldSize;
	this->dimensions = dimensions;
	this->scale.x = gridWorldSize.x / dimensions.x;
	this->scale.y = gridWorldSize.y / dimensions.y;

	this->init();
}


Grid::~Grid()
{

}

void Grid::AStar(bool visualize, RenderWindow* window)
{	
	//Define the two lists "OPEN" and "CLOSED"
	std::vector<Node*> OPEN;
	std::vector<Node*> CLOSED;

	//Initialization
	Node* node_start = &this->grid[start.x][start.y];
	Node* node_goal = &this->grid[end.x][end.y];

	node_start->g = Node::heuristic(*node_start, *node_start);
	node_start->h = Node::heuristic(*node_start, *node_goal);

	OPEN.push_back(node_start);
	node_start->isInOpen = true;
	while (OPEN.size() > 0)
	{
		Node* node_current = OPEN[0];
		int indexOpen = 0;

		//Find the node with the lowest f-cost in "OPEN" (node_current)
		for (int i = 0; i < OPEN.size(); i++)
		{
			if (OPEN[i]->get_f() < node_current->get_f())
			{
				node_current = OPEN[i];
				indexOpen = i;
			}
		}

		//Remove "node_current" from "OPEN" and add to "CLOSED"
		OPEN.erase(OPEN.begin() + indexOpen);
		node_current->isInOpen = false;

		CLOSED.push_back(node_current);
		node_current->isInClosed = true;

		if (node_current == node_goal) //Path has been found
		{
			Grid::pathFound = true;
			this->retracePath(node_start, node_goal);
			break;
		}

		//Loop over each surrounding nodes (node_neighbour)

		for (Node* node_neighbour : this->getNeighbours(node_current))
		{
			//Skip to the next node
			if (node_neighbour->isInClosed || !node_neighbour->walkable)
			{
				continue;
			}
			int new_g = node_current->g + Node::heuristic(*node_current, *node_neighbour);
			if (new_g < node_neighbour->g || !node_neighbour->isInOpen)
			{
				node_neighbour->g = new_g;
				node_neighbour->h = Node::heuristic(*node_neighbour, *node_goal);
				node_neighbour->parent = node_current;

				if (!node_neighbour->isInOpen)
				{
					OPEN.push_back(node_neighbour);
					node_neighbour->isInOpen = true;
				}
			}
		}
		if (visualize) {
			this->pollEvents(*window);
			window->clear();
			this->draw(*window);
			node_current->draw(*window, Color(100, 191, 255), this->scale);
			window->display();
		}
	}
}

void Grid::AStarFibb(bool visualize, RenderWindow* window)
{
	//Define the two FibonacciHeaps "OPEN" and "CLOSED"
	FibonacciHeap<Node*> OPEN;
	FibonacciHeap<Node*> CLOSED;

	//Initialization
	Node* node_start = &this->grid[start.x][start.y];
	Node* node_goal = &this->grid[end.x][end.y];

	node_start->g = Node::heuristic(*node_start, *node_start);
	node_start->h = Node::heuristic(*node_start, *node_goal);

	OPEN.insert(node_start);
	node_start->isInOpen = true;
	while (!OPEN.isEmpty())
	{
		Node* node_current = OPEN.getMinimum();

		//Remove "node_current" from "OPEN" and add to "CLOSED"
		OPEN.removeMinimum();
		node_current->isInOpen = false;

		CLOSED.insert(node_current);
		node_current->isInClosed = true;

		if (node_current == node_goal) //Path has been found
		{
			Grid::pathFound = true;
			this->retracePath(node_start, node_goal);
			break;
		}

		//Loop over each surrounding nodes (node_neighbour)

		for (Node* node_neighbour : this->getNeighbours(node_current))
		{
			//Skip to the next node
			if (node_neighbour->isInClosed || !node_neighbour->walkable)
			{
				continue;
			}
			int new_g = node_current->g + Node::heuristic(*node_current, *node_neighbour);
			if (new_g < node_neighbour->g || !node_neighbour->isInOpen)
			{
				node_neighbour->g = new_g;
				node_neighbour->h = Node::heuristic(*node_neighbour, *node_goal);
				node_neighbour->parent = node_current;

				if (!node_neighbour->isInOpen)
				{
					OPEN.insert(node_neighbour);
					node_neighbour->isInOpen = true;
				}
			}
		}
		if (visualize) {
			this->pollEvents(*window);
			window->clear();
			this->draw(*window);
			node_current->draw(*window, Color(100, 191, 255), this->scale);
			window->display();
		}

	}
}


void Grid::retracePath(Node *startNode, Node *endNode)
{
	std::vector<Node> path;
	Node *node_current = endNode;

	while (node_current != startNode)
	{
		path.push_back(*node_current);
		if (node_current != endNode) node_current->isInPath = true;
		node_current = node_current->parent;
	}
	std::reverse(path.begin(), path.end());
	this->path = path;
}

const std::vector<Node*> Grid::getNeighbours(const Node *node)
{
	std::vector<Node*> neighbours;

	for (int x = -1; x <= 1; x += 1)
	{
		for (int y = -1; y <= 1; y += 1)
		{
			//skip self
			if (x == 0 && y == 0) continue;
			////4 directions (staright)
			//if (x == -1 && y == -1) continue;
			//if (x == 1 && y == -1) continue;
			//if (x == -1 && y == 1) continue;
			//if (x == 1 && y == 1) continue;
			////4 directions (Diagonal)
			//if (x == 0 && y == -1) continue;
			//if (x == -1&& y == 0) continue;
			//if (x == 1 && y == 0) continue;
			//if (x == 0 && y == 1) continue;

			Vector2i check = Vector2i(node->worldPosition.x + x, node->worldPosition.y + y);
			if (check.x >= 0 && check.x < this->dimensions.x && check.y >= 0 && check.y < this->dimensions.y)
			{
				neighbours.push_back(&this->grid[check.x][check.y]);
			}
		}
	}
	return neighbours;
}

void Grid::draw(RenderWindow & window)
{
	for (size_t x = 0; x < this->grid.size(); x++)
	{
		for (size_t y = 0; y < this->grid[x].size(); y++)
		{
			Node* currentNode = &this->grid[x][y];

			Color fillColor;

			if (currentNode->isInPath) fillColor = Color(255, 215, 0);
			else {
				if (currentNode->walkable) fillColor = Color::White;
				else fillColor = Color::Blue;
			}
			if (!Grid::pathFound)
			{
				if (currentNode->isInOpen) fillColor = Color(173, 255, 47);
				if (currentNode->isInClosed) fillColor = Color(240, 128, 128);
			}
			if (x == this->start.x && y == this->start.y) fillColor = Color(0, 150, 0);
			else if (x == this->end.x && y == this->end.y) fillColor = Color::Red;

			currentNode->draw(window, fillColor, this->scale);
		}
	}
}

void Grid::zoomViewAt(Vector2i pixel, RenderWindow& window, float zoom)
{
	const Vector2f beforeCoord{ window.mapPixelToCoords(pixel) };
	View view{ window.getView() };
	view.zoom(zoom);
	window.setView(view);
	const Vector2f afterCoord{ window.mapPixelToCoords(pixel) };
	const Vector2f offsetCoords{ beforeCoord - afterCoord };
	view.move(offsetCoords);
	window.setView(view);
}

void Grid::pollEvents(RenderWindow &window)
{
	//Events
	Event event;
	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed)
			window.close();
		if (event.type == Event::MouseWheelScrolled)
		{
			if (event.mouseWheelScroll.delta > 0)
				Grid::zoomViewAt({ event.mouseWheelScroll.x, event.mouseWheelScroll.y }, window, (1.f / 1.05));
			else if (event.mouseWheelScroll.delta < 0)
				Grid::zoomViewAt({ event.mouseWheelScroll.x, event.mouseWheelScroll.y }, window, 1.05);
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::Escape))
		window.close();
}

bool Grid::pathFound = false;