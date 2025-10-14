#pragma once
#include "Game/GameObject.hpp"

class PhysicsManager {
  public:
	void ApplyPhysics(GameObject &obj, const float timeStep) const;

  private:
	const float gravity = 1000.0f;
};