#pragma once
#include "Engine/ECS/Components/Core/VelocityComponent.hpp"
#include "Engine/ECS/Components/Gameplay/MovementComponent.hpp"
#include "Engine/ECS/Components/Gameplay/PlayerStateComponent.hpp"
#include "Engine/ECS/Registry.hpp"

namespace GameEngine::ECS::Systems {
class PlayerStateSystem {
  public:
	static void Update(Registry &registry)
	{
		auto view = registry.view<PlayerStateComponent, VelocityComponent, MovementComponent>();
		for (auto entity : view) {
			auto &state = view.get<PlayerStateComponent>(entity);
			auto &vel = view.get<VelocityComponent>(entity);
			auto &move = view.get<MovementComponent>(entity);
			if (!move.grounded) {
				if (vel.velocity.y < 0) {
					state.Current = PlayerStateType::Jumping;
				} else {
					state.Current = PlayerStateType::Falling;
				}
			} else {
				if (std::abs(vel.velocity.x) > 0.1f) {
					state.Current = PlayerStateType::Walking;
				} else {
					state.Current = PlayerStateType::Idle;
				}
			}
		}
	}
};
} // namespace GameEngine::ECS::Systems