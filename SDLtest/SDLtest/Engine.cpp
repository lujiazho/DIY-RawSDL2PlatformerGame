#include "Engine.h"
#include "TextureManager.h"
#include <iostream>
#include "Transform.h"
#include "Warrior.h"
#include "Enemy.h"
#include "Input.h"
#include "Timer.h"
#include "MapParser.h"
#include <iostream>
#include "Camera.h"
#include "ObjectFactory.h"


Engine* Engine::s_Instance = nullptr;

bool Engine::Init() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0 && IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG)!=0) {
		SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
		return false;
	}

	SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

	m_Window = SDL_CreateWindow("Soft Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, window_flags);
	if (m_Window == nullptr) {
		SDL_Log("Failed to create Window: %s", SDL_GetError());
		return false;
	}

	m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_Renderer == nullptr) {
		SDL_Log("Failed to create Renderer: %s", SDL_GetError());
		return false;
	}

	if (!MapParser::GetInstance()->Load()) {
		std::cout << "Failed to load map" << std::endl;
	}

	m_LevelMap = MapParser::GetInstance()->GetMap("MAP");

	TextureManager::GetInstance()->ParseTextures("assets/textures.tml");
	/*TextureManager::GetInstance()->Load("player", "assets/character/Warrior/Individual Sprite/idle/idle.png");
	TextureManager::GetInstance()->Load("player_run", "assets/character/Warrior/Individual Sprite/Run/run.png");
	TextureManager::GetInstance()->Load("player_jump", "assets/character/Warrior/Individual Sprite/Jump/jump.png");
	TextureManager::GetInstance()->Load("player_fall", "assets/character/Warrior/Individual Sprite/Fall/fall.png");
	TextureManager::GetInstance()->Load("player_crouch", "assets/character/Warrior/Individual Sprite/Crouch/crouch.png");
	TextureManager::GetInstance()->Load("player_attack", "assets/character/Warrior/Individual Sprite/Attack/attack.png");
	TextureManager::GetInstance()->Load("bg", "assets/bg2.jpg");*/

	//Warrior* player = new Warrior(new Properties("player", 100, 200, 64, 44)); // position and width and height of img
	//Enemy* tBettle = new Enemy(new Properties("tBettle_idle", 820, 240, 1192, 1102));
	
	/*std::string textureID, int x, int y, int width, int height, float attacktime, float attackedtime, int walkforce, int damage,
		std::vector<std::string>* sprites, std::vector<int>* spritesLen, std::vector<int>* spritesSpeed, SDL_RendererFlip flip = SDL_FLIP_NONE*/
	GameObject* player = ObjectFactory::GetInstance()->CreateObject("PLAYER", new Properties("player", 100, 200, 64, 44, 20.0, 10.0, 0, 2, NULL, NULL, NULL));
	GameObject* tBettle = ObjectFactory::GetInstance()->CreateObject("tBettle", new Properties("tBettle_appear", 820, 250, 1192, 1102, 75.0, 10.0, 0, 20, NULL, NULL, NULL));
	GameObject* tBettle1 = ObjectFactory::GetInstance()->CreateObject("tBettle", new Properties("tBettle_appear", 420, 200, 1192, 1102, 75.0, 10.0, 0, 20, NULL, NULL, NULL));
	m_GameObjects.push_back(player);
	m_GameObjects.push_back(tBettle);
	m_GameObjects.push_back(tBettle1);
	for (int i = 300; i < 2000; i += 200) {
		m_GameObjects.push_back(ObjectFactory::GetInstance()->CreateObject("ENEMY", new Properties("undead", i, 200, 56, 32, 20.0, 10.0, 2, 5,
			new std::vector<std::string>{ "undead", "undead_walk", "undead_attack", "undead_hurt", "undead_die" },
			new std::vector<int>{ 18, 20, 20, 16, 13 },
			new std::vector<int>{ 100, 50, 20, 200, 100 })));
		m_GameObjects.push_back(ObjectFactory::GetInstance()->CreateObject("ENEMY", new Properties("skeleton", i+100, 200, 50, 48, 40.0, 10.0, 4, 10,
			new std::vector<std::string>{ "skeleton", "skeleton_run", "skeleton_attack", "skeleton_hurt", "skeleton_die" },
			new std::vector<int>{ 3, 6, 6, 3, 6 },
			new std::vector<int>{ 100, 30, 20, 200, 100 })));
	}

	Camera::GetInstance()->SetTarget(player->GetOrigin());
	Camera::GetInstance()->SetSceneLimit(SCREEN_WIDTH*10, SCREEN_HEIGHT);
	return m_IsRunning = true;
}

bool Engine::Clean() {
	for (unsigned int i = 0; i != m_GameObjects.size(); i++) {
		m_GameObjects[i]->Clean();
	}
	TextureManager::GetInstance()->Clean();
	SDL_DestroyRenderer(m_Renderer);
	SDL_DestroyWindow(m_Window);
	IMG_Quit();
	SDL_Quit();
	return true;
}

void Engine::Update() {
	float dt = Timer::GetInstance()->getDeltaTime();
	m_LevelMap->Update();
	for (unsigned int i = 0; i != m_GameObjects.size(); i++) {
		m_GameObjects[i]->Update(dt);
	}
	if (((Warrior*)m_GameObjects[0])->IsDead()) {
		m_IsRunning = false;
	}
	Camera::GetInstance()->Update(dt);
}

void Engine::Render() {
	SDL_SetRenderDrawColor(m_Renderer, 124, 218, 254, 255);
	SDL_RenderClear(m_Renderer);

	TextureManager::GetInstance()->Draw("bg", 0, 0, 2110, 1050, 0.7, 0.7, 0.1); // scaleX和Y代表背景在XY上的放缩
	m_LevelMap->Render();

	//TextureManager::GetInstance()->Draw("tree", 100, 100, 347, 465, SDL_FLIP_NONE);
	for (unsigned int i = 0; i != m_GameObjects.size(); i++) {
		m_GameObjects[i]->Draw();
	}

	SDL_RenderPresent(m_Renderer);
}

void Engine::Events() {
	Input::GetInstance()->Listen();
}

void Engine::Quit() {
	m_IsRunning = false;
}