#include "Engine.h"
#include "Timer.h"

int main(int, char**) {
	Engine::GetInstance()->Init();

	while (Engine::GetInstance()->IsRunning()) {
		Engine::GetInstance()->Events();
		Engine::GetInstance()->Update();
		Engine::GetInstance()->Render();
		Timer::GetInstance()->Tick();
	}

	Engine::GetInstance()->Clean();
	return 0;
}