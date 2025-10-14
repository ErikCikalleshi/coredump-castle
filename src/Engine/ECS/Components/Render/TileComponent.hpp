#pragma once
#include <glm/vec2.hpp>

struct TileComponent {
	float TileSize = 32;
	glm::vec2 TileMapPosition = {0, 0};
};