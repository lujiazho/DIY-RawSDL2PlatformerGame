#ifndef INPUT_H
#define INPUT_H

#include "SDL.h"

enum Axis {HORIZONTAL, VERTICAL};

class Input {
public:
	static Input* GetInstance() {
		return s_Instance = (s_Instance != nullptr) ? s_Instance : new Input();
	}

	void Listen();
	bool GetKeyDown(SDL_Scancode key);

	int GetAxisKey(Axis axis);

private:
	Input();
	void KeyUp();
	void KeyDown();

	const Uint8* m_KeyStates; // 1 pushed 0 not pushed
	static Input* s_Instance;
};

#endif // INPUT_H