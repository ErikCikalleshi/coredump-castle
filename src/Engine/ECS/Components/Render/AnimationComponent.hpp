#pragma once
#include "Engine/Graphics/Animation.hpp"
#include <vector>

enum AnimationState { ANIM_IDLE, ANIM_WALK, ANIM_JUMP, ANIM_FALL };

struct AnimationComponent {
	std::vector<Animation> animations;
	AnimationState currentAnimation{ANIM_IDLE};
};