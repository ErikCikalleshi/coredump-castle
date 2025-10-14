#pragma once
struct MovementComponent {
	float accelerationRate{2000.0f};
	float maxSpeedX{300.0f};
	float jumpForce{-300.0f};
	bool grounded{true};
};
