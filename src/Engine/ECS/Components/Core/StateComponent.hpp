#pragma once

enum States { Idle, Walking, Jumping, Falling, Attacking, Crouching };

struct StateComponent {
	int state = 0;
};