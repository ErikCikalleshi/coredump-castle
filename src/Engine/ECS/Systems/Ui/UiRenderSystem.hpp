#pragma once
#include "Engine/ECS/Components/Gameplay/TooltipComponent.hpp"
#include "Engine/ECS/Components/Render/TextDisplayComponent.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Graphics/Renderer.hpp"

namespace GameEngine::ECS {
class Registry;
}

namespace GameEngine::ECS::Systems {
class UiRenderSystem {
  public:
	explicit UiRenderSystem(Renderer &renderer);
	void update(Registry &registry, const GameEngine &game) const;
	void initTextDisplayComp(const std::string &text, TextDisplayComponent &textDisplay, const GameEngine &game) const;

  private:
	// NOLINTNEXTLINE(cppcoreguidelines-avoid-const-or-ref-data-members): never null, owner outlives this object
	Renderer &renderer;
	glm::vec2 resolutionSize{0.f, 0.f};
};

} // namespace GameEngine::ECS::Systems
