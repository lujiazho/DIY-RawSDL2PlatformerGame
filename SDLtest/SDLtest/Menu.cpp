#include "Menu.h"
#include "Play.h"
#include "Engine.h"
#include "Input.h"

Menu::Menu() {}

bool Menu::Init() {
	m_Ctxt = Engine::GetInstance()->GetRenderer();
	std::cout << "menu initialized" << std::endl;
	return true;
}

void Menu::Render() {
	SDL_SetRenderDrawColor(m_Ctxt, 16, 45, 70, 255);
	SDL_RenderClear(m_Ctxt);

	SDL_RenderPresent(m_Ctxt);
}

void Menu::Update() {

}

bool Menu::Exit() {
	std::cout << "exit menu!" << std::endl;
	return true;
}

// callbacks
void Menu::StartGame() {
	std::cout << "start game!\n" << std::endl;
}

void Menu::Editor() {
	std::cout << "editor mode!\n" << std::endl;
}

void Menu::Settings() {
	std::cout << "options mode!\n" << std::endl;
}

void Menu::Quit() {
	std::cout << "quit game!\n" << std::endl;
}