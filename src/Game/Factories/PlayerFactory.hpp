#pragma once
#include "Engine/ECS/Components/Core/PositionComponent.hpp"
#include "Engine/ECS/Components/Core/VelocityComponent.hpp"
#include "Engine/ECS/Components/Physics/AccelerationComponent.hpp"
#include "Engine/ECS/Components/Render/AnimationComponent.hpp"
#include "Engine/ECS/Components/Render/SpriteComponent.hpp"
#include "Engine/ECS/Components/Gameplay/MovementComponent.hpp"
#include "Engine/ECS/Components/Gameplay/InputComponent.hpp"

#include "Engine/ECS/Registry.hpp"
#include "Engine/ECS/Components/Physics/GravityComponent.hpp"
#include "Engine/Graphics/TextureManager.hpp"


struct PlayerFactory {
    static GameEngine::ECS::Entity CreatePlayer(GameEngine::ECS::Registry &registry, TextureManager &texMgr,
                                                float x = 0.0f, float y = 0.0f) {
        auto e = registry.create();
        registry.register_component(e, PositionComponent{.position = {x, y}});
        registry.register_component(e, VelocityComponent{.velocity = {0.0f, 0.0f}});
        registry.register_component(e, AccelerationComponent{.acceleration = {0.0f, 0.0f}});
        registry.register_component(e, GravityComponent{});

        registry.register_component(e, SpriteComponent{texMgr.GetTexture("assets/player/char_blue_1.png"), 56});
        registry.register_component(e, AnimationComponent{
                                        std::vector<Animation>{
                                            Animation(6, 0.6f), // ANIM_IDLE
                                            Animation(8, 0.8f), // ANIM_WALK
                                            Animation(8, 0.4f, false), // ANIM_JUMP
                                            Animation(8, 0.4f, false) // ANIM_FALL
                                        },
                                        ANIM_IDLE
                                    });
        registry.register_component(e, MovementComponent{});
        registry.register_component(e, InputComponent{});

        return e;
    }
};
