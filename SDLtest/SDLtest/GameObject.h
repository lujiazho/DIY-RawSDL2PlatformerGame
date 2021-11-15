#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "IObject.h"
#include "Transform.h"
#include "SDL.h"
#include "Point.h"
#include <vector>
#include <string>

struct Properties {
public:
	Properties(std::string textureID, int x, int y, int width, int height, float attacktime, float attackedtime, int walkforce, int damage,
		std::vector<std::string>* sprites, std::vector<int>* spritesLen, std::vector<int>* spritesSpeed, SDL_RendererFlip flip = SDL_FLIP_NONE) {
		X = x;
		Y = y;
		Flip = flip;
		Height = height;
		Width = width;
		TextureID = textureID;
		AttackedTime = attackedtime;
		AttackTime = attacktime;
		WalkForce = walkforce;
		Damage = damage;
		Sprites = sprites;
		SpritesLen = spritesLen;
		SpritesSpeed = spritesSpeed;
	}

public:
	std::string TextureID;
	int Width, Height;
	float X, Y;
	float AttackedTime, AttackTime;
	int WalkForce;
	int Damage;
	SDL_RendererFlip Flip;
	std::vector<std::string>* Sprites;
	std::vector<int>* SpritesLen;
	std::vector<int>* SpritesSpeed;
};

class GameObject : public IObject {
public:
	GameObject(Properties* props):m_TextureID(props->TextureID),m_Width(props->Width),
		m_Height(props->Width), m_Flip(props->Flip){
		m_Transform = new Transform(props->X, props->Y);

		float px = props->X + props->Width / 2;
		float py = props->Y + props->Height / 2;
		m_Origin = new Point(px, py);
	}

	inline Point* GetOrigin() { m_Origin->X = m_Transform->X; m_Origin->Y = m_Transform->Y; return m_Origin; }
	inline int GetWidth() { return m_Width; }
	inline int GetHeight() { return m_Height; }
	
	virtual void Draw() = 0;
	virtual void Update(float dt) = 0;
	virtual void Clean() = 0;

protected:
	Point* m_Origin;
	Transform* m_Transform;
	int m_Width, m_Height;
	std::string m_TextureID;
	SDL_RendererFlip m_Flip;
};

#endif // GAMEOBJECT_H