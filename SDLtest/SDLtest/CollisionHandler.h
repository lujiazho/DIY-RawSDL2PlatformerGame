#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H

#include "SDL.h"
#include <vector>
#include "TileLayer.h"
#include "GameMap.h"
#include "Engine.h"
#include "Point.h"

class CollisionHandler {
public:
	bool MapCollision(SDL_Rect a);
	bool CheckCollision(SDL_Rect a, SDL_Rect b);
	bool CheckCollisionWithPlayer(SDL_Rect a);
	bool CheckUnderAttackRange(SDL_Rect a);

	void SetPlayerAttacked();
	void SetUnderDamage(int damage);
	Point* GetPlayerPosition() { return m_player->GetOrigin(); }

	inline static CollisionHandler* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new CollisionHandler(); }
private:
	CollisionHandler();
	TileMap m_CollisionTilemap;
	TileLayer* m_CollisionLayer;
	static CollisionHandler* s_Instance;

	GameObject* m_player;
};

#endif // COLLISIONHANDLER_H