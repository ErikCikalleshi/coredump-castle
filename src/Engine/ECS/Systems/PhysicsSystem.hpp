#pragma once
#include "Engine/ECS/Components/Core/PositionComponent.hpp"
#include "Engine/ECS/Components/Core/VelocityComponent.hpp"
#include "Engine/ECS/Components/Gameplay/MovementComponent.hpp"
#include "Engine/ECS/Components/Physics/AccelerationComponent.hpp"
#include "Engine/ECS/Registry.hpp"
#include <glm/glm.hpp>

#include "Engine/ECS/Components/Physics/GravityComponent.hpp"

namespace GameEngine::ECS::Systems {
    class PhysicsSystem {
    public:
        static void Update(Registry &registry, float timeStep) {
            // Gravity

            auto viewGravity = registry.view<VelocityComponent, GravityComponent>();
            for (auto entity: viewGravity) {
                auto& vel = viewGravity.get<VelocityComponent>(entity);
                auto& grav = viewGravity.get<GravityComponent>(entity);
                vel.velocity += glm::vec2(0, grav.gravity) * timeStep;
            }


            auto view = registry.view<PositionComponent, VelocityComponent, AccelerationComponent, MovementComponent>();
            for (auto entity: view) {
                auto &pos = view.get<PositionComponent>(entity);
                auto &vel = view.get<VelocityComponent>(entity);
                auto &acc = view.get<AccelerationComponent>(entity);
                auto &move = view.get<MovementComponent>(entity);

                // SDL_Log("Position: (%.2f, %.2f), Velocity: (%.2f, %.2f), Acceleration: (%.2f, %.2f)", pos.position.x,
                //         pos.position.y, vel.velocity.x, vel.velocity.y, acc.acceleration.x, acc.acceleration.y);

                vel.velocity += acc.acceleration * timeStep;
                if (std::abs(vel.velocity.x) > move.maxSpeedX) {
                    vel.velocity.x = move.maxSpeedX * (vel.velocity.x > 0 ? 1 : -1);
                }
                pos.position += vel.velocity * timeStep;
            };
        };
    };
} // namespace GameEngine::ECS::Systems
