#pragma once
#include <memory>
#include <SDL3/SDL.h>
#include <glm/glm.hpp>
#include "../Engine/Graphics/TextureManager.hpp"
#include "../Engine/Graphics/Renderer.hpp"

class GameObject {
public:
	GameObject(Renderer& renderer) :renderer(renderer) {
		direction = 1;
		maxSpeedX = accelerationRate = jumpForce = 0;
		position = velocity = acceleration = glm::vec2(0);
		collisionBox = { 0 };
	};
	virtual ~GameObject() = default;
	virtual void Update(const float deltaTime, const float stepSize) = 0;
	virtual void Render() = 0;


	std::shared_ptr<SDL_Texture> texture;
	SDL_FRect collisionBox;
	Renderer& renderer;
	float spriteSize = 32;
	bool dynamic = false;
	glm::vec2 position, velocity, acceleration;
	float direction, maxSpeedX, accelerationRate, jumpForce;
};