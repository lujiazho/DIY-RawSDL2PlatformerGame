//#include "Play.h"
//#include "Gui.h"
//
//Gui::Frame* frame = nullptr;
//
//Play::Play() {}
//
//bool Play::Init() {
//	m_EditMode = false;
//	m_Ctxt = Engine::GetInstance()->GetRenderer();
//
//	TextureManager::GetInstance()->ParseTextures("assets/textures.tml");
//	m_LevelMap = MapParser::GetInstance()->Load("assets/maps/map.tmx");
//	TileLayer* collisionLayer = (TileLayer*)m_LevelMap->GetLayers.back();
//
//	int tilesize = collisionLayer->GetTileSize();
//	int width = collisionLayer->GetWidth() * tilesize;
//	int height = collisionLayer->GetHeight() * tilesize;
//
//	Camera::GetInstance()->SetSceneLimit(width, height);
//	CollisionHandler::GetInstance()->SetCollisionMap(CollisionLayer->GetTileMap(), tilesize);
//
//	Warrior* warrior = new Warrior(new Properties("player", 100, 200, 64, 44));
//	Camera::GetInstance()->SetTarget(warrior->GetOrigin());
//	m_GameObjects.push_back(warrior);
//
//	frame = new Gui::Frame(Gui::Attr(m_Ctxt, 100, 100, 500, 300));
//
//	Gui::Frame* f2 = new Gui::Frame(Gui::Attr(m_Ctxt, 100, 100, 250, 100));
//	f2->Addchild(new Gui::Slider(Gui::Attr(m_Ctxt, 50, 50, 200, 5)));
//
//	frame->AddChild(f2);
//	std::cout << "play initialized!" << std::endl;
//	return true;
//}
//
//void Play::Render() {
//	SDL_SetRenderDrawColor(m_Ctxt, 48, 96, 130, 255);
//	SDL_RenderClear(m_Ctxt);
//
//	m_LevelMap->Render();
//	
//	for (auto gameobj : m_GameObjects) {
//		gameobj->Draw();
//	}
//
//	SDL_Rect camera = Camera::GetInstance()->GetViewBox();
//
//	if (m_EditMode) {
//		Gui::GetInstance()->draw(m_Ctxt);
//	}
//
//	SDL_RenderCopy(m_Ctxt, nullptr, &camera, nullptr);
//	SDL_RenderPresent(m_Ctxt);
//}
//
//void Play::Update() {
//	Events();
//
//	if (!m_EditMode) {
//		float dt = Timer::GetInstance()->getDeltaTime();
//
//		for (auto gameobj : m_GameObjects) {
//			gameobj->Update(dt);
//		}
//		Camera::GetInstance()->Update();
//		m_LevelMap->Update();
//	}
//}
//
//void Play::Events() {
//
//	if (!m_EditMode && Input::GetInstance()->GetKeyDown(SDL_SCANCODE_M)) {
//		Engine::GetInstance()->ChangeState(new Menu());
//	}
//
//	if (!m_EditMode && Input::GetInstance()->GetKeyDown(SDL_SCANCODE_ESCAPE)) {
//		m_EditMode = true;
//		SDL_Delay(100);
//	}
//
//	if (m_EditMode && Input::GetInstance()->GetKeyDown(SDL_SCANCODE_F5)) {
//		m_EditMode = false;
//		SDL_Delay(100);
//	}
//}
//
//bool Play::Exit() {
//	m_LevelMap->Clean();
//	delete m_LevelMap;
//
//	for (auto gameobj : m_GameObjects) {
//		gameobj->Clean();
//		delete gameobj;
//	}
//
//	m_GameObjects.clear();
//	TextureManager::GetInstance()->Clean();
//	std::cout << "exit play" << std::endl;
//	return true;
//}
//
//void Play::OpenMenu() {
//	Engine::GetInstance()->ChangeState(new Menu());
//}
//
//void Play::PauseGame() {
//
//}