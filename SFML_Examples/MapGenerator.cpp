#include "MapGenerator.h"
#include <limits>

MapGenerator::MapGenerator(int seed, Vector2i mapDimensions, float noiseScale, int octaves, float persistance, float lacunarity, Vector2f offset, float elevation)
{
	if (mapDimensions.x < 1) mapDimensions.x = 1;
	if (mapDimensions.y < 1) mapDimensions.y = 1;
	if (lacunarity < 1) lacunarity = 1;
	if (octaves < 0) octaves = 0;

	this->seed = seed;
	this->mapDimensions = mapDimensions;
	this->noiseScale = noiseScale;
	this->octaves = octaves;
	this->persistance = persistance;
	this->lacunarity = lacunarity;
	this->offset = offset;
	this->elevation = elevation;

	this->noiseMap = MapGenerator::generateNoiseMap(this->seed, this->mapDimensions.x, this->mapDimensions.y, this->noiseScale, this->octaves, this->persistance, this->lacunarity, this->offset);
	this->initTerrainTypes();
	this->updateTexture();
}


MapGenerator::~MapGenerator()
{
}

void MapGenerator::initTerrainTypes()
{
	this->regions.push_back(Terrain(TerrainType::WATER_DEEP, 0.3f, Color(50, 80, 170)));
	this->regions.push_back(Terrain(TerrainType::WATER_SHALLOW, 0.4f, Color(55, 102, 196)));
	this->regions.push_back(Terrain(TerrainType::SAND, 0.45f, Color(208, 208, 128)));
	this->regions.push_back(Terrain(TerrainType::GRASS_LIGHT, 0.55f, Color(85, 151, 24)));
	this->regions.push_back(Terrain(TerrainType::GRASS_DARK, 0.6f, Color(64, 106, 22)));
	this->regions.push_back(Terrain(TerrainType::ROCK_LIGHT, 0.7f, Color(93, 69, 64)));
	this->regions.push_back(Terrain(TerrainType::ROCK_DARK, 0.9f, Color(76, 59, 58)));
	this->regions.push_back(Terrain(TerrainType::SNOW, 0.95f, Color(255, 255, 255)));
}

void MapGenerator::draw(RenderWindow * window)
{
	window->draw(this->sprite);
}

void MapGenerator::update(const float & dt, const float & multiplier)
{
	this->noiseMap = MapGenerator::generateNoiseMap(this->seed, this->mapDimensions.x, this->mapDimensions.y, this->noiseScale, this->octaves, this->persistance, this->lacunarity, this->offset);
	this->updateTexture();
}


void MapGenerator::updateTexture()
{
	this->texture.clear();
	this->texture.create(this->mapDimensions.x, this->mapDimensions.y);

	for (size_t y = 0; y < this->mapDimensions.y; y++)
	{
		for (size_t x = 0; x < this->mapDimensions.x; x++)
		{
			float currentHeight = pow(this->noiseMap[x][y], this->elevation);
			//MapGenerator::addSquareMask(x, y, currentHeight, (this->mapDimensions.x + this->mapDimensions.y)/2);
			RectangleShape cell;
			cell.setPosition(x, y);
			cell.setOutlineThickness(0);
			cell.setSize(Vector2f(1.f, 1.f));

			for (auto& region : this->regions)
			{
				if (currentHeight <= region.height)
				{
					cell.setFillColor(Color(region.color));
					break;
				}
			}

			this->texture.draw(cell);
		}
	}
	this->texture.display();
	this->sprite.setTexture(this->texture.getTexture());
}

float MapGenerator::addSquareMask(const int &x, const int &y, float &noise, float island_size)
{
	float distance_x = fabs(x - island_size * 0.5f);
	float distance_y = fabs(y - island_size * 0.5f);
	float distance = fmax(distance_x, distance_y); // square mask

	float max_width = island_size * 0.5f - 10.0f;
	float delta = distance / max_width;
	float gradient = delta * delta;

	noise *= fmax(0.0f, 1.f - gradient);
	return noise;
}

float MapGenerator::addCircleMask(const int & x, const int & y, float & noise, float island_size)
{
	float distance_x = fabs(x - island_size * 0.5f);
	float distance_y = fabs(y - island_size * 0.5f);
	float distance = sqrt(distance_x*distance_x + distance_y * distance_y); // circular mask

	float max_width = island_size * 0.5f - 10.0f;
	float delta = distance / max_width;
	float gradient = delta * delta;

	noise *= fmax(0.0f, 1.0f - gradient);
	return noise;
}

void MapGenerator::setDisplaySize(const Vector2f &size)
{
	 Vector2f scale = Vector2f(size.x/this->texture.getSize().x, size.y/this->texture.getSize().y);
	this->sprite.setScale(scale);
}

std::vector<std::vector<float>> MapGenerator::generateNoiseMap(const int & seed, const unsigned int & width, const unsigned int & height, float & scale, const int &octaves, const float &persistance, const float &lacunarity, const sf::Vector2f& offset)
{
	std::vector<std::vector<float>> noiseMap(width, std::vector<float>(height, 0));

	srand(seed);
	PerlinNoise pn(seed);

	std::vector<sf::Vector2f> octaveOffsets;
	for (size_t i = 0; i < octaves; i++)
	{
		float offsetX = (rand() % (1000000 - (-1000000) + 1) - 1000000) + offset.x;
		float offsetY = (rand() % (1000000 - (-1000000) + 1) - 1000000) + offset.y;
		octaveOffsets.push_back(sf::Vector2f(offsetX, offsetY));
	}

	if (scale <= 0)
	{
		scale = 0.0001f;
	}

	float maxNoiseHeight = std::numeric_limits<float>::min();
	float minNoiseHeight = std::numeric_limits<float>::max();

	float halfWidth = width / 2;
	float halfHeight = height / 2;

	for (size_t y = 0; y < height; y++)
	{
		for (size_t x = 0; x < width; x++)
		{
			float amplitude = 1;
			float frequency = 1;
			float noiseHeight = 0;

			for (size_t i = 0; i < octaves; i++)
			{
				float sampleX = (x - halfWidth) / scale * frequency + octaveOffsets[i].x;
				float sampleY = (y - halfHeight) / scale * frequency + octaveOffsets[i].y;

				float perlinValue = pn.noise(sampleX, sampleY) * 2 - 1;
				noiseHeight += perlinValue * amplitude;
				amplitude *= persistance;
				frequency *= lacunarity;

			}

			if (noiseHeight > maxNoiseHeight)
			{
				maxNoiseHeight = noiseHeight;
			}
			else if (noiseHeight < minNoiseHeight)
			{
				minNoiseHeight = noiseHeight;
			}
			noiseMap[x][y] = noiseHeight;
		}
	}
	//Normalize noisemap
	for (size_t y = 0; y < height; y++)
	{
		for (size_t x = 0; x < width; x++)
		{
			noiseMap[x][y] = PerlinNoise::invLerp(minNoiseHeight, maxNoiseHeight, noiseMap[x][y]);
		}
	}
	return noiseMap;
}