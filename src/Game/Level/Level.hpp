#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <memory>
#include <tileson.hpp>

#include "../GameObject.hpp"
#include "../Entities/Player.hpp"

class Level: public GameObject{
public: 
	Level(TextureManager& textureManager, Renderer& renderer);
	
	void Load(const std::string& levelFile, Player& player);
	void Update(const float deltaTime, const float stepSize);
	void Render();

	const std::unique_ptr<tson::Map>& GetMap() const { return map; }

private:
	std::unique_ptr<tson::Map> map = nullptr;
	tson::Tileson t;
	glm::ivec2 dimensions;
	TextureManager& textureManager;
};