#include "Engine/GameEngine.hpp"
#include "Engine/DebugSystem.hpp"

constexpr float stepSize = 1.0f / 240.0f;
float accumulator = 0.0f;

int main()
{
	GameEngine::GameEngine game("Coredump Castle", 1920, 1080);
	if (!game.Init())
		return EXIT_FAILURE;

	Uint64 prevTime = SDL_GetTicks();
	while (game.Running()) {
		const Uint64 currentTime = SDL_GetTicks();
		const float deltaTime = (currentTime - prevTime) / 1000.0f;

		//DebugSystem::Debug(std::to_string(1000 / deltaTime));

		game.HandleEvents();

		accumulator += deltaTime;
		while (accumulator >= stepSize) {
			accumulator -= stepSize;
			game.Update(deltaTime, stepSize);
		}
		game.Render();
		prevTime = currentTime;
	}
	game.Cleanup();
	return EXIT_SUCCESS;
}