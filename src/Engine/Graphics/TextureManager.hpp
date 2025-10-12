#pragma once
#include <SDL3/SDL.h>
#include <string>
#include <unordered_map>
#include <optional>
#include <memory>

class Renderer;

class TextureManager {
public:
	TextureManager(Renderer& renderer) :renderer(renderer) {};

	std::shared_ptr<SDL_Texture> GetTexture(const std::string& filePath);

	void Cleanup() { textures.clear(); }

private:
	std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> textures;
	Renderer& renderer;
};