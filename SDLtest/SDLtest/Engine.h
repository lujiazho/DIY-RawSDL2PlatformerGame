#ifndef ENGINE_H
#define ENGINE_H

#include "SDL.h"
#include "SDL_image.h"
#include "GameMap.h"
#include "GameObject.h"
#include "GameState.h"

#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 640

class Engine {

public:
	static Engine* GetInstance() {
		return s_Instance = (s_Instance != nullptr)? s_Instance : new Engine();
	}

	bool Init();
	bool Clean();
	void Quit();

	void Update();
	void Render();
	void Events();

	void PopState(); // �洢״̬
	void PushState(GameState* current); // pop ǰҪpush
	void ChangeState(GameState* target);

	inline GameMap* GetMap() { return m_LevelMap; }
	inline bool IsRunning() { return m_IsRunning; }
	inline SDL_Renderer* GetRenderer() { return m_Renderer; }

	inline SDL_Window* GetMainWindow() { return m_Window; }
	inline GameObject* GetPlayer() { return m_GameObjects[0]; }

private:
	Engine() {}
	bool m_IsRunning;

	GameMap* m_LevelMap;
	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;
	static Engine* s_Instance;

	std::vector<GameObject*> m_GameObjects;

	std::vector<GameState*> m_States;
};

#endif // ENGINE_H