#include "SeqAnimation.h"
#include "Vendor/TinyXML/tinyxml.h"
#include <iostream>
#include "TextureManager.h"
#include "Camera.h"

SeqAnimation::SeqAnimation(bool repeat) :Animation(repeat) {}

void SeqAnimation::DrawFrame(float x, float y, float xScale, float yScale, SDL_RendererFlip flip) {
	//Vector2D cam = Camera::GetInstance()->GetPosition(); // 自己加的，不知道为何，只为了防止怪位移
	TextureManager::GetInstance()->Draw(m_CurrentSeq.TextureIDs[m_CurrentFrame], x, y, m_CurrentSeq.Width, m_CurrentSeq.Height, xScale, yScale, 1, flip);
}

void SeqAnimation::Update(float dt) {
	if (m_Repeat || !m_IsEnded) {
		m_IsEnded = false;
		m_CurrentFrame = (SDL_GetTicks() / m_CurrentSeq.Speed) % m_CurrentSeq.FrameCount;
	}
	if (m_CurrentFrame == (m_CurrentSeq.FrameCount-1)) {
		m_IsEnded = true;
		if (!m_Repeat) // if not repeat, just stay in the last frame
			m_CurrentFrame = m_CurrentSeq.FrameCount - 1;
		else // if repeat, come back to 0 frame
			m_CurrentFrame = 0;
	}
}

void SeqAnimation::SetCurrentSeq(std::string seqID) {
	if (m_SeqMap.count(seqID) > 0) {
		m_CurrentSeq = m_SeqMap[seqID];
	}
	else {
		std::cout << "The given Sequence animation is not matching: " << seqID << std::endl; // seq就是不同的动作序列, 分开的那种
	}
}

void SeqAnimation::Parse(std::string source) {
	TiXmlDocument xml;
	xml.LoadFile(source);
	if (xml.Error()) {
		std::cout << "Failed to load animation file: " << source << std::endl;
	}

	TiXmlElement* root = xml.RootElement();
	for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
		if (e->Value() == std::string("sequence")) {
			Sequence seq;
			std::string seqID = e->Attribute("id");
			e->Attribute("speed", &seq.Speed);
			e->Attribute("width", &seq.Width);
			e->Attribute("height", &seq.Height);
			e->Attribute("frameCount", &seq.FrameCount);
			for (TiXmlElement* frame = e->FirstChildElement(); frame != nullptr; frame = frame->NextSiblingElement()) {
				seq.TextureIDs.push_back(frame->Attribute("textureID"));
			}
			m_SeqMap[seqID] = seq;
		}
	}
}
