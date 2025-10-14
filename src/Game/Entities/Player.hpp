#pragma once
#include "Engine/Graphics/Animation.hpp"
#include "Engine/Input/InputManager.hpp"
#include "IEntity.hpp"

enum PlayerState { IDLE, WALKING, JUMPING, FALLING };

class Player : public IEntity {
	// Inherited via IEntity
	void Update(const float deltaTime, const float stepSize) override;
	void Render() override;
	void SetGrounded(bool grounded) override;

  public:
	Player(const InputManager &inputManager, TextureManager &textureManager, Renderer &renderer);

  private:
	void ReadInput();
	void UpdateMovement(const float stepSize);
	void UpdateAnimation();
	void MoveHorizontal(const float currentDirection, const float stepSize);

	// input
	const InputManager &inputManager;
	bool jumpPressed = false;

	// animations
	Renderer &renderer;
	PlayerState state = IDLE;
	const int ANIM_IDLE = 0;
	const int ANIM_WALK = 2;
	const int ANIM_JUMP = 3;
	const int ANIM_FALL = 4;
	bool flip = false;
};