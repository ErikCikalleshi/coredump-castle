#include "PhysicsManager.hpp"

void PhysicsManager::ApplyPhysics(GameObject &obj, const float timeStep) const
{
	if (!obj.dynamic)
		return;

	// Apply gravity
	obj.velocity += glm::vec2(0, gravity) * timeStep;

	obj.velocity += obj.acceleration * timeStep;
	if (std::abs(obj.velocity.x) > obj.maxSpeedX) {
		obj.velocity.x = obj.maxSpeedX * (obj.velocity.x > 0 ? 1 : -1);
	}
	obj.position += obj.velocity * timeStep;
}