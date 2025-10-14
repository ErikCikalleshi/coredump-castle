#pragma once
#include <SDL3/SDL.h>
#include <memory>

enum Layer { Background = 0, Parallax = 1, Tiles = 2, Entities = 3, Player = 4, Foreground = 5 };

struct SpriteComponent {
	std::shared_ptr<SDL_Texture> texture;
	float spriteSize = 32;
	bool flipX = false;
	Layer layer = Tiles;
};