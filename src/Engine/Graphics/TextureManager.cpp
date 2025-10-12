#include "TextureManager.hpp"
#include "Renderer.hpp"
#include  <stdexcept>


std::shared_ptr<SDL_Texture> TextureManager::GetTexture(const std::string& filePath) {
    auto it = textures.find(filePath);
    if (it != textures.end()) {
        return it->second; // already loaded
    }

    // Load new texture using unique_ptr from Renderer
    auto texUnique = renderer.LoadTexture(filePath);

    // Convert to shared_ptr with custom deleter
    std::shared_ptr<SDL_Texture> texShared(texUnique.release(), SDLTextureDeleter{});
    textures[filePath] = texShared;
    return texShared;
}
