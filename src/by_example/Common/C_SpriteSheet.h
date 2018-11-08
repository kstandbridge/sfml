#pragma once
#include "C_Drawable.h"
#include "SpriteSheet.h"

class C_SpriteSheet : public C_Drawable
{
public:
	C_SpriteSheet() : C_Drawable(Component::SpriteSheet), m_spriteSheet(nullptr)
	{
	}

	~C_SpriteSheet()
	{
		if(m_spriteSheet) delete m_spriteSheet;
	}


	void ReadIn(std::stringstream& stream) override
	{
		stream >> m_sheetName;
	}

	void Create(TextureManager* textureManager, const std::string& name = "")
	{
		if(m_spriteSheet) return;
		m_spriteSheet = new SpriteSheet(textureManager);
		m_spriteSheet->LoadSheet(
			"media/SpriteSheets/" + (name != "" ? name : m_sheetName) + ".sheet");
	}

	SpriteSheet* GetSpriteSheet()
	{
		return m_spriteSheet;
	}

	void UpdatePosition(const sf::Vector2f& vec) override
	{
		m_spriteSheet->SetSpritePosition(vec);
	}

	const sf::Vector2u& GetSize() override
	{
		return m_spriteSheet->GetSpriteSize();
	}

	void Draw(sf::RenderWindow* window) override
	{
		if(!m_spriteSheet) return;
		m_spriteSheet->Draw(window);
	}

private:
	SpriteSheet* m_spriteSheet;
	std::string m_sheetName;
};


