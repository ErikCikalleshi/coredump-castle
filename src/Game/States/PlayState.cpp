#include "PlayState.hpp"
#include "Engine/ECS/Systems/AnimationSystem.hpp"
#include "Engine/ECS/Systems/CollisionSystem.hpp"
#include "Engine/ECS/Systems/MovementSystem.hpp"
#include "Engine/ECS/Systems/PhysicsSystem.hpp"
#include "Engine/ECS/Systems/JumpSystem.hpp"
#include "Engine/ECS/Systems/StateSystem.hpp"
#include "Engine/GameEngine.hpp"
#include "Game/Factories/LevelFactory.hpp"

namespace GameEngine {

void PlayState::Init(GameEngine &game)
{
	LevelFactory factory(game.registry, textureManager);
	factory.CreateLevel("assets/maps/Level1.json");
}

void PlayState::Cleanup() {}

void PlayState::Pause() {}

void PlayState::Resume() {}

void PlayState::HandleEvents(GameEngine &game) {}

// TODO Cleanup
void PlayState::Update(GameEngine &game, const float deltaTime, const float stepSize)
{

	inputSystem.Update(game.registry);

	ECS::Systems::JumpSystem::Update(game.registry);
	ECS::Systems::MovementSystem::Update(game.registry, stepSize);
	ECS::Systems::PhysicsSystem::Update(game.registry, stepSize);
	ECS::Systems::CollisionSystem::Update(game.registry);

	ECS::Systems::StateSystem::Update(game.registry);
	ECS::Systems::AnimationSystem::Update(game.registry, stepSize);
}

void PlayState::Render(GameEngine &game)
{
	game.GetRenderer().StartFrame(25, 25, 25, 255);
	renderSystem.Update(game.registry);
	game.GetRenderer().EndFrame();
}
} // namespace GameEngine