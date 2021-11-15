#include "CollisionHandler.h"
#include "Engine.h"
#include "Warrior.h"

CollisionHandler* CollisionHandler::s_Instance = nullptr;

CollisionHandler::CollisionHandler() {
	m_CollisionLayer = (TileLayer*)Engine::GetInstance()->GetMap()->GetMapLayers().front();
	m_CollisionTilemap = m_CollisionLayer->GetTilemap();
	m_player = Engine::GetInstance()->GetPlayer();
}

void CollisionHandler::SetPlayerAttacked() { 
	((Warrior*)m_player)->SetAttacked(); 
}

void CollisionHandler::SetUnderDamage(int damage) {
	((Warrior*)m_player)->SetUnderDmage(damage);
}

bool CollisionHandler::CheckUnderAttackRange(SDL_Rect a) {
	int x = a.x - 400, y = a.y, w = 1596, h = 1152;
	bool x_overlaps = (a.x < m_player->GetOrigin()->X + m_player->GetWidth()) && (a.x + a.w > m_player->GetOrigin()->X);
	bool y_overlaps = (a.y < m_player->GetOrigin()->Y + m_player->GetHeight()) && (a.y + a.h > m_player->GetOrigin()->Y);
	return (x_overlaps && y_overlaps);
}

bool CollisionHandler::CheckCollisionWithPlayer(SDL_Rect a) {
	bool x_overlaps = (a.x < m_player->GetOrigin()->X + m_player->GetWidth()) && (a.x + a.w > m_player->GetOrigin()->X);
	bool y_overlaps = (a.y < m_player->GetOrigin()->Y + m_player->GetHeight()) && (a.y + a.h > m_player->GetOrigin()->Y);
	return (x_overlaps && y_overlaps && ((Warrior*)m_player)->IsAttacking());
}

bool CollisionHandler::CheckCollision(SDL_Rect a, SDL_Rect b) {
	bool x_overlaps = (a.x < b.x + b.w) && (a.x + a.w > b.x);
	bool y_overlaps = (a.y < b.y + b.h) && (a.y + a.h > b.y);
	return (x_overlaps && y_overlaps);
}

bool CollisionHandler::MapCollision(SDL_Rect a) {
	int tileSize = 32;
	int RowCount = m_CollisionLayer->GetRowCount();
	int ColCount = m_CollisionLayer->GetColCount();

	int left_tile = a.x / tileSize;
	int right_tile = (a.x + a.w) / tileSize;

	int top_tile = a.y / tileSize;
	int bottom_tile = (a.y + a.h) / tileSize;

	if (left_tile < 0) left_tile = 0;
	if (right_tile > ColCount) right_tile = ColCount;

	if (top_tile < 0) top_tile = 0;
	if (bottom_tile > RowCount) bottom_tile = RowCount;

	for (int i = left_tile; i <= right_tile; i++) {
		for (int j = top_tile; j <= bottom_tile; j++) {
			if (m_CollisionTilemap[j][i] > 0) {
				return true;
			}
		}
	}
	return false;
}