#pragma once
#include "Engine/Graphics/Animation.hpp"
#include <vector>
#include <unordered_map>

struct AnimationComponent {
	std::vector<Animation> animations;
	int currentAnimation;

	std::unordered_map<int, int> stateToAnimationIndex;
};