#include "Anim_Directional.h"
#include "SpriteSheet.h"


void Anim_Directional::FrameStep()
{
	if(m_frameStart < m_frameEnd) 
		++m_frameCurrent;
	else 
		--m_frameCurrent;

	if((m_frameStart < m_frameEnd && m_frameCurrent > m_frameEnd) ||
		(m_frameStart > m_frameEnd && m_frameCurrent < m_frameEnd))
	{
		if(m_loop)
		{
			m_frameCurrent = m_frameStart;
			return;
		}
		m_frameCurrent = m_frameEnd;
		Pause();
	}
}

void Anim_Directional::CropSprite()
{
	auto size = m_spriteSheet->GetSpriteSize();
	sf::IntRect rect(
		size.x * m_frameCurrent, 
		size.y * (m_frameRow + (short)m_spriteSheet->GetDirection()),
		size.x,
		size.y);
	m_spriteSheet->CropSprite(rect);
}

void Anim_Directional::ReadIn(std::stringstream& stream)
{
	stream >> m_frameStart 
		   >> m_frameEnd 
		   >> m_frameRow 
		   >> m_frameTime 
		   >> m_frameActionStart 
		   >> m_frameActionEnd;
}
