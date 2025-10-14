#include "PlayState.hpp"
#include "Engine/ECS/Systems/AnimationSystem.hpp"
#include "Engine/ECS/Systems/MovementSystem.hpp"
#include "Engine/ECS/Systems/PhysicsSystem.hpp"
#include "Engine/ECS/Systems/PlayerStateSystem.hpp"
#include "Engine/GameEngine.hpp"
#include "Game/Entities/Player.hpp"
#include "Game/Factories/PlayerFactory.hpp"
#include "Game/Level/Level.hpp"

namespace GameEngine {

void PlayState::Init(GameEngine &game)
{
	glm::vec2 spawnPoint;

	std::unique_ptr<Level> level = std::make_unique<Level>(textureManager, renderer);
	level->Load("assets/maps/Level1.json", spawnPoint);
	this->level = level.get();

	PlayerFactory::CreatePlayer(game.registry, textureManager, spawnPoint.x, spawnPoint.y);

	gameObjects.emplace_back(std::move(level));
	// gameObjects.emplace_back(std::move(player));
}

void PlayState::Cleanup() {}

void PlayState::Pause() {}

void PlayState::Resume() {}

void PlayState::HandleEvents(GameEngine &game) {}

// TODO Cleanup
void PlayState::Update(GameEngine &game, const float deltaTime, const float stepSize)
{

	inputSystem.Update(game.registry);

	ECS::Systems::MovementSystem::Update(game.registry, stepSize);
	// 1. Update all entities and apply physics
	for (auto &entity : gameObjects) {
		entity->Update(deltaTime, stepSize);
		physicsManager.ApplyPhysics(*entity, stepSize);
	}
	ECS::Systems::PhysicsSystem::Update(game.registry, stepSize);
	ECS::Systems::PlayerStateSystem::Update(game.registry);
	ECS::Systems::AnimationSystem::Update(game.registry, stepSize);
	collisionSystem.Resolve(gameObjects, deltaTime);
}

void PlayState::Render(GameEngine &game)
{
	game.GetRenderer().StartFrame(25, 25, 25, 255);

	// game.GetRenderer().CenterCameraOn(*player);

	for (auto &entity : gameObjects) {
		entity->Render();
	}
	renderSystem.Update(game.registry);

	level->RenderForeground();

	game.GetRenderer().EndFrame();
}
} // namespace GameEngine