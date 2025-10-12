#pragma once
#include <glm/glm.hpp>
#include <SDL3/SDL.h>
#include <vector>
#include <memory>
#include "../Engine/Graphics/Animation.hpp"
#include "../AnimatedGameObject.hpp"

class IEntity : public AnimatedGameObject {
public:
	IEntity(TextureManager& textureManager, Renderer& renderer) : AnimatedGameObject(textureManager, renderer) {};
	virtual ~IEntity() = default;
	virtual void Update(const float deltaTime, const float stepSize) = 0;
	virtual void SetGrounded(bool grounded) = 0;

protected:
	bool grounded = false;
};