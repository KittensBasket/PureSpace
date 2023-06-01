#ifndef CORE_GAME_CONSTANTS_HPP
#define CORE_GAME_CONSTANTS_HPP

#include <vector>

struct vertex {
	float x, y;
};

struct polygon{
	unsigned short a, b, c;
};

struct instance {
	float x, y;
	float angle;
};

const std::vector<vertex> SQUARE_VERTICES = {{0.5f, 0.5f}, {0.5f, -0.5f}, {-0.5f, -0.5f}, {-0.5f, 0.5f}};
const std::vector<vertex> SQUARE_TEXTURE_COORDS = {{1.f, 1.f}, {1.f, 0.f}, {0.f, 0.f}, {0.f, 1.f}};
const std::vector<polygon> SQUARE_POLYGONS = {{0, 1, 3}, {1, 2, 3}};

const unsigned int MAX_CHMONYA_INSTANCES_CNT = 1024;

#endif // CORE_GAME_CONSTANTS_HPP