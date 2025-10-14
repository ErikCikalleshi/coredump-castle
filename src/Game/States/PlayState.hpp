#pragma once
#include "Engine/ECS/Systems/InputSystem.hpp"
#include "Engine/ECS/Systems/RenderSystem.hpp"
#include "Game/GameObject.hpp"
#include "Engine/GameState.hpp"

namespace GameEngine {

class PlayState : public GameState {
	// Inherited via GameState
  public:
	PlayState(const InputManager &input, TextureManager &textureManager, Renderer &renderer,
	          PhysicsManager &physicsManager, const CollisionSystem &collisionSystem)
	    : inputManager(input), textureManager(textureManager), renderer(renderer), physicsManager(physicsManager),
	      collisionSystem(collisionSystem)
	{
	}
	void Init(GameEngine &game) override;
	void Cleanup() override;
	void Pause() override;
	void Resume() override;
	void HandleEvents(GameEngine &game) override;
	void Update(GameEngine &game, const float deltaTime, const float stepSize) override;
	void Render(GameEngine &game) override;

  private:
	std::vector<std::unique_ptr<GameObject>> gameObjects;
	Level *level = nullptr;
	const InputManager &inputManager;
	TextureManager &textureManager;
	Renderer &renderer;
	PhysicsManager &physicsManager;
	ECS::Systems::RenderSystem renderSystem{renderer};
	ECS::Systems::InputSystem inputSystem{inputManager};
	const CollisionSystem &collisionSystem;
};
} // namespace GameEngine