#ifndef SPRITEANIMATION_H
#define SPRITEANIMATION_H

#include "SDL.h"
#include <string>
#include "Animation.h"

class SpriteAnimation : public Animation{
public:
	SpriteAnimation(bool repeat = true);

	virtual void Update(float dt);
	void Draw(float x, float y, int spriteWidth, int spriteHeight, float xScale = 1, float yScale = 1, SDL_RendererFlip flip = SDL_FLIP_NONE);
	// textureID is name, spriteRow is which row the character located in, frameCount means hou much frame this state account for 
	void SetProps(std::string textureID, int spriteRow, int frameCount, int animSpeed);

private:
	int m_SpriteRow;
	int m_AnimSpeed;
	int m_FrameCount;
	std::string m_TextureID;
};

#endif // SPRITEANIMATION_H