#include "LevelFactory.hpp"

#include "glm/vec2.hpp"


void LevelFactory::CreateLevel(const std::string &levelFile) {
    tson::Tileson t;
    auto map = t.parse(fs::path(levelFile));
    if (map->getStatus() != tson::ParseStatus::OK) {
        throw std::runtime_error("Failed to load map: " + map->getStatusMessage());
    }
    fs::path imagePath = map->getTilesets().at(0).getFullImagePath();
    imagePath = "assets/tilesets" / imagePath.filename();
    auto tileSetTexture = textureManager.GetTexture(imagePath.string());

    // Load Background Textures

    if (tson::Layer *backgroundLayer = map->getLayer("Background");
        backgroundLayer && backgroundLayer->getType() == tson::LayerType::Group) {
        for (tson::Layer layer: backgroundLayer->getLayers()) {
            if (layer.getType() != tson::LayerType::ImageLayer)
                return;

            std::string layername = layer.getName();
            fs::path backgroundPath = layer.getImage();
            backgroundPath = "assets/background" / backgroundPath.filename();
            if (layername == "Background") {
                texture = textureManager.GetTexture(backgroundPath.string());
            } else if (layername == "Parallax") {
                // TODO: Support multiple parallax layers with different scroll factors
                parallaxTexture = textureManager.GetTexture(backgroundPath.string());
            } else if (layername == "Foreground") {
                foregroundTexture = textureManager.GetTexture(backgroundPath.string());
            }
        }
    }

    // Set player position to spawn point
    const auto spawnPointFromMap = map->getLayer("Entities")->getObjectsByName("Player");
    if (spawnPointFromMap.size() != 1 && !spawnPointFromMap.at(0).isPoint()) {
        throw std::runtime_error("Map must have exactly one Player spawn point");
    }
    const tson::Vector2 pos = spawnPointFromMap.at(0).getPosition();
    spawnPoint = glm::vec2(pos.x, pos.y);
}
