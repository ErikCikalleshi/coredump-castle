#pragma once
#include "Engine/ECS/Components/Core/PositionComponent.hpp"
#include "Engine/ECS/Components/Render/AnimationComponent.hpp"
#include "Engine/ECS/Components/Render/BackgroundComponent.hpp"
#include "Engine/ECS/Components/Render/RenderComponent.hpp"
#include "Engine/ECS/Components/Render/TextureComponent.hpp"
#include "Engine/ECS/Components/Render/TileComponent.hpp"
#include "Engine/ECS/Registry.hpp"
#include "Engine/ECS/View.hpp"
#include "Engine/Graphics/Renderer.hpp"
#include <algorithm>

namespace GameEngine::ECS::Systems {
class RenderSystem {
  public:
	RenderSystem(Renderer &renderer) : renderer(renderer) {}

	void Update(Registry &registry)
	{
		renderItems.clear();
		// Backgrounds
		auto bgView = registry.view<TextureComponent, RenderComponent, BackgroundComponent>();
		for (auto entity : bgView) {
			auto &tex = bgView.get<TextureComponent>(entity);
			auto &render = bgView.get<RenderComponent>(entity);
			auto &bg = bgView.get<BackgroundComponent>(entity);

			std::optional<SDL_FRect> srcOpt;
			std::optional<SDL_FRect> dstOpt;

			const SDL_FRect *src = nullptr;
			SDL_FRect *dst = nullptr;
			if (render.layer == Layer::Parallax) {
				dstOpt = SDL_FRect{.x = -bg.scrollPos,
				                   .y = bg.yOffset,
				                   .w = tex.texture->w * 5.0f,
				                   .h = static_cast<float>(tex.texture->h)};
			}

			renderItems.push_back(RenderItem{.Layer = render.layer,
			                                 .texture = tex.texture.get(),
			                                 .src = srcOpt,
			                                 .dst = dstOpt,
			                                 .parallax = (render.layer == Layer::Parallax),
			                                 .flipX = render.flipX});
		}

		// Tiles, Player
		auto view = registry.view<PositionComponent, TextureComponent, TileComponent, RenderComponent>();
		for (auto entity : view) {
			auto &pos = view.get<PositionComponent>(entity);
			auto &tex = view.get<TextureComponent>(entity);
			auto &tile = view.get<TileComponent>(entity);
			auto &render = view.get<RenderComponent>(entity);

			const SDL_FRect src{
			    .x = tile.TileMapPosition.x, .y = tile.TileMapPosition.y, .w = tile.TileSize, .h = tile.TileSize};

			SDL_FRect dst{.x = pos.position.x, .y = pos.position.y, .w = tile.TileSize, .h = tile.TileSize};

			renderItems.push_back(RenderItem{.Layer = render.layer,
			                                 .texture = tex.texture.get(),
			                                 .src = src,
			                                 .dst = dst,
			                                 .parallax = false,
			                                 .flipX = render.flipX});

			// TODO : Re-add debug rendering
			// if (DebugSystem::Instance().render.showBoundingBoxes) {
			//	SDL_SetRenderDrawColor(renderer.get(), 255, 0, 0, 255);
			//	const SDL_FRect box{.x = obj.position.x + obj.collisionBox.x,
			//	                    .y = obj.position.y + obj.collisionBox.y,
			//	                    .w = obj.collisionBox.w,
			//	                    .h = obj.collisionBox.h};
			//	SDL_RenderRect(renderer.get(), &box);
			//}
		}

		std::sort(renderItems.begin(), renderItems.end(),
		          [](const RenderItem &a, const RenderItem &b) { return a.Layer < b.Layer; });

		for (auto &renderItem : renderItems) {
			if (!renderItem.parallax) {
				renderer.RenderTexture(*renderItem.texture, renderItem.src, renderItem.dst, renderItem.flipX);
			} else {
				renderer.RenderTextureTiled(*renderItem.texture, renderItem.dst.value(), 1);
			}
		}
		renderItems.clear();
	}

  private:
	struct RenderItem {
		int Layer;
		SDL_Texture *texture;
		std::optional<SDL_FRect> src;
		std::optional<SDL_FRect> dst;
		bool parallax;
		bool flipX;
	};
	std::vector<RenderItem> renderItems;

	Renderer &renderer;
};
} // namespace GameEngine::ECS::Systems