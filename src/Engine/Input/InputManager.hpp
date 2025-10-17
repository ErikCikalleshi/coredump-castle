#pragma once
#include "Key.hpp"
#include <SDL3/SDL.h>
#include <unordered_map>

class InputManager {
  public:
	InputManager();
	void Update(const SDL_KeyboardEvent *e);
	bool IsKeyDown(Key key) const;
	bool IsKeyPressed(Key key) const;  // Key was just pressed this frame
	bool IsKeyReleased(Key key) const; // Key was just released this frame

  private:
	std::unordered_map<Key, bool> currentKeyStates;
	std::unordered_map<Key, bool> previousKeyStates;
	std::unordered_map<SDL_Scancode, Key> scancodeMapping;
};