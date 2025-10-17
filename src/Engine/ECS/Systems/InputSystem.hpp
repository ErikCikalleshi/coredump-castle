#pragma once
#include "Engine/ECS/Components/Gameplay/InputComponent.hpp"
#include "Engine/ECS/Registry.hpp"
#include "Engine/Input/InputManager.hpp"
#include "Engine/ECS/View.hpp"      

namespace GameEngine::ECS::Systems {
class InputSystem {
  public:
	InputSystem(const InputManager &inputManager) : inputManager(inputManager) {}

	void Update(Registry &registry)
	{
		float horizontalDirection = 0;
		if (inputManager.IsKeyDown(Key::Left)) {
			horizontalDirection += -1;
		}
		if (inputManager.IsKeyDown(Key::Right)) {
			horizontalDirection += 1;
		}

		auto view = registry.view<InputComponent>();
		for (auto &entity : view) {
			auto &input = view.get<InputComponent>(entity);
			input.horizontalDirection = horizontalDirection;
			input.jumpPressed = inputManager.IsKeyPressed(Key::Up);
		}
	}

  private:
	const InputManager &inputManager;
};
} // namespace GameEngine::ECS::Systems