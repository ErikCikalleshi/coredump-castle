#pragma once
#include <glm/glm.hpp>
#include <memory>
#include <tileson.hpp>
#include <vector>

#include "../Entities/Player.hpp"
#include "../GameObject.hpp"

class Level : public GameObject {
  public:
	Level(TextureManager &textureManager, Renderer &renderer);

	void Load(const std::string &levelFile, glm::vec2 &spawnPoint);
	void Update(const float deltaTime, const float stepSize);
	void Render();
	void RenderForeground() const;

	const std::unique_ptr<tson::Map> &GetMap() const { return map; }

  private:
	void RenderTiles(SDL_Texture &texture, const tson::Layer &layer) const;
	void RenderBackground();

	std::unique_ptr<tson::Map> map = nullptr;
	tson::Tileson t;
	glm::ivec2 dimensions;
	std::shared_ptr<SDL_Texture> tileSetTexture = nullptr;
	std::shared_ptr<SDL_Texture> parallaxTexture = nullptr;
	std::shared_ptr<SDL_Texture> foregroundTexture = nullptr;
	TextureManager &textureManager;
	float scrollPos = 0.0f;
};