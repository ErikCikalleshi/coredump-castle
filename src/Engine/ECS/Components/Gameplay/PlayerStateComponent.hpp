#pragma once
enum PlayerStateType { Idle, Walking, Jumping, Falling };

struct PlayerStateComponent {
	PlayerStateType Current = PlayerStateType::Idle;
};
