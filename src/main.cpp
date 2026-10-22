#include "Engine/GameEngine.hpp"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

namespace {
struct LoopContext {
	GameEngine::GameEngine game;
	Uint64 prevTime;
};

void tick(LoopContext &ctx)
{
	PROFILE_SCOPE("MainLoop");
	const Uint64 currentTime = SDL_GetTicks();
	const float deltaTime = static_cast<float>(currentTime - ctx.prevTime) / 1000.0f;
	ctx.prevTime = currentTime;

	ctx.game.handleEvents();
	ctx.game.update(deltaTime);
	ctx.game.render(deltaTime);
}
} // namespace

int main()
{
	constexpr int windowWidth = 1920;
	constexpr int windowHeight = 1080;

#ifdef __EMSCRIPTEN__
	// The browser owns the main loop, so the context has to outlive main().
	static LoopContext ctx{GameEngine::GameEngine("Coredump Castle", Resolution{.width = windowWidth, .height = windowHeight}),
	                       0};
	if (!ctx.game.init())
		return EXIT_FAILURE;
	ctx.prevTime = SDL_GetTicks();

	emscripten_set_main_loop_arg(
	    [](void *arg) {
		    auto &loopCtx = *static_cast<LoopContext *>(arg);
		    if (!loopCtx.game.isRunning()) {
			    emscripten_cancel_main_loop();
			    return;
		    }
		    tick(loopCtx);
	    },
	    &ctx, 0, true);
	return EXIT_SUCCESS;
#else
	LoopContext ctx{GameEngine::GameEngine("Coredump Castle", Resolution{.width = windowWidth, .height = windowHeight}),
	                0};
	if (!ctx.game.init())
		return EXIT_FAILURE;
	ctx.prevTime = SDL_GetTicks();

	while (ctx.game.isRunning())
		tick(ctx);
	ctx.game.cleanup();
	return EXIT_SUCCESS;
#endif
}
