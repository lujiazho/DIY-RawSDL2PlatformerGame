#ifndef CONDITION_H
#define CONDITION_H

#include "SDL.h"
#include "Camera.h"

class Condition {
public:
	Condition(int life = 100, int mana = 100) { 
		m_currentLifePoint = life; 
		m_currentManaPoint = mana;
		m_LifePoint = life; 
		m_ManaPoint = mana; 
	}

	int GetLifePoint() { return m_currentLifePoint; }
	int GetManaPoint() { return m_currentManaPoint; }

	inline void SetBuffer(int x, int y, int w, int h) { m_Buffer = { x, y, w, h }; }

	void Set(int x, int y, int w, int h) {
		m_Box = {
			x - m_Buffer.x,
			y - m_Buffer.y,
			w - m_Buffer.w,
			h - m_Buffer.h
		};
	}

	void ChangeLifePoint(int amount) {
		m_currentLifePoint += amount;
		if (m_currentLifePoint < 0){
			m_currentLifePoint = 0;
		}
		if (m_currentLifePoint > m_LifePoint) {
			m_currentLifePoint = m_LifePoint;
		}
	}

	void Draw() {
		Vector2D cam = Camera::GetInstance()->GetPosition();
		SDL_Rect box = { 
			(int)(m_Box.x - cam.X), (int)(m_Box.y - cam.Y), 
			m_Box.w * m_currentLifePoint / m_LifePoint, m_Box.h };
		SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 255, 0, 0, 1);
		SDL_RenderFillRect(Engine::GetInstance()->GetRenderer(), &box);
	}

private:
	int m_currentLifePoint;
	int m_currentManaPoint;
	int m_LifePoint;
	int m_ManaPoint;
	SDL_Rect m_Box;
	SDL_Rect m_Buffer;
};

#endif // CONDITION_H