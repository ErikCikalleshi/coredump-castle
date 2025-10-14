#pragma once

#include "../Components/Render/AnimationComponent.hpp"
#include "../Registry.hpp"

namespace GameEngine::ECS::Systems {
class AnimationSystem {
  public:
	static void Update(Registry &registry, float stepSize)
	{
		auto view = registry.view<AnimationComponent>();
		for (auto entity : view) {
			auto &anim = view.get<AnimationComponent>(entity);
			if (anim.currentAnimation != -1) {
				anim.animations.at(anim.currentAnimation).step(stepSize);
			}
		}
	}
};
} // namespace GameEngine::ECS::Systems
