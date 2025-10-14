#pragma once

enum PlayerState { IDLE, WALKING, JUMPING, FALLING };

struct PlayerStateComponent {
	PlayerState state{IDLE};
	float direction{0.0f};
};