#include "Engine/ECS/Components/Render/RenderComponent.hpp"
#include "Engine/ECS/Registry.hpp"
#include "Engine/Graphics/TextureManager.hpp"

#include <tileson.hpp>

class LevelFactory {
  public:
	LevelFactory(GameEngine::ECS::Registry &registry, TextureManager &textureManager)
	    : registry(registry), textureManager(textureManager) {};
	void CreateLevel(const std::string &levelFile);

	void SpawnPlayer(std::unique_ptr<tson::Map> &map);



  private:
	void LoadTiles(std::unique_ptr<tson::Map> &map);
	void LoadBackground(std::unique_ptr<tson::Map> &map );
	void CreateBackground(const fs::path &filename, const Layer &layer, const float scrollSpeed = 0,
	                      const float yOffset = 0);

	GameEngine::ECS::Registry &registry;
	TextureManager &textureManager;

};
