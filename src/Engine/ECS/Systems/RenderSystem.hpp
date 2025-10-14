#pragma once
#include "Engine/ECS/Components/Core/PositionComponent.hpp"
#include "Engine/ECS/Components/Render/AnimationComponent.hpp"
#include "Engine/ECS/Components/Render/SpriteComponent.hpp"
#include "Engine/ECS/Registry.hpp"
#include "Engine/ECS/View.hpp"
#include "Engine/Graphics/Renderer.hpp"

namespace GameEngine::ECS::Systems {
class RenderSystem {
  public:
	RenderSystem(Renderer &renderer) : renderer(renderer) {}

	void Update(Registry &registry)
	{
		// Animated entities
		auto animatedView = registry.view<PositionComponent, SpriteComponent, AnimationComponent>();
		for (auto entity : animatedView) {
			auto &pos = animatedView.get<PositionComponent>(entity);
			auto &sprite = animatedView.get<SpriteComponent>(entity);
			auto &anim = animatedView.get<AnimationComponent>(entity);

			const float srcX = anim.currentAnimation != -1
			                       ? anim.animations.at(anim.currentAnimation).currentFrame() * sprite.spriteSize
			                       : 0;
			const float srcY = anim.currentAnimation != -1 ? anim.currentAnimation * sprite.spriteSize : 0;

			const SDL_FRect src{.x = srcX, .y = srcY, .w = sprite.spriteSize, .h = sprite.spriteSize};

			SDL_FRect dst{.x = pos.position.x, .y = pos.position.y, .w = sprite.spriteSize, .h = sprite.spriteSize};

			renderer.RenderTexture(*(sprite.texture), src, dst, sprite.flipX);

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
	}

  private:
	Renderer &renderer;
};
} // namespace GameEngine::ECS::Systems