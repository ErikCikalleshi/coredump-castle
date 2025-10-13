#pragma once
#include "../Engine/Graphics/Animation.hpp"
#include "GameObject.hpp"
#include <vector>

class AnimatedGameObject : public GameObject {
  public:
	AnimatedGameObject(TextureManager &textureManager, Renderer &renderer)
	    : GameObject(renderer), currentAnimation(0) {};
	virtual ~AnimatedGameObject() = default;

	std::vector<Animation> animations;
	int currentAnimation;

	void Update(const float deltaTime, const float stepSize) override
	{
		animations.at(currentAnimation).step(deltaTime);
	};
};