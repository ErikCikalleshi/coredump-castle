#include "Engine/ECS/Registry.hpp"
#include "Engine/Graphics/TextureManager.hpp"
#include <tileson.hpp>

class LevelFactory {
public:
    LevelFactory(GameEngine::ECS::Registry &registry, TextureManager &textureManager) : registry(registry),
        textureManager(textureManager) {
    };

    void CreateLevel(const std::string &levelFile);

private:
    static void CreateBackground();

    GameEngine::ECS::Registry &registry;
    TextureManager &textureManager;
};



inline void LevelFactory::CreateBackground() {
}
