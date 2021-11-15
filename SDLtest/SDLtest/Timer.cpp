#include "Timer.h"
#include "SDL.h"

Timer* Timer::s_Instance = nullptr;

// a dynamic method for dt calculation which depends on your cpu and moniter fps
void Timer::Tick() {
	m_DeltaTime = (SDL_GetTicks() - m_LastTime) * (TARGET_FPS / 1000.0f);

	if (m_DeltaTime > TARGET_DELTATIME) {
		m_DeltaTime = TARGET_DELTATIME;
	}
	m_LastTime = SDL_GetTicks();
}