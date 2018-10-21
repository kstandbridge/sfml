#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "TextureManager.h"
#include  "Anim_Directional.h"
#include "Utilities.h"
#include <unordered_map>


using Animations = std::unordered_map<std::string, Anim_Base*>;

class SpriteSheet
{
public:
	SpriteSheet(TextureManager* textureManager);

	~SpriteSheet() { ReleaseSheet(); }

	void CropSprite(const sf::IntRect& rect);
	sf::Vector2i GetSpriteSize() const;
	sf::Vector2f GetSpritePosition() const;
	void SetSpriteSize(const sf::Vector2i& size);
	void SetSpritePosition(const sf::Vector2f& pos);

	void SetDirection(const Direction& dir);
	Direction GetDirection() const;

	bool LoadSheet(const std::string& file);
	void ReleaseSheet();

	Anim_Base* GetCurrentAnim();
	bool SetAnimation(const std::string& name, const bool& play = false, const bool& loop = false);

	void Update(const float& deltaTime);
	void Draw(sf::RenderWindow* window);

private:
	std::string m_texture;
	sf::Sprite m_sprite;
	sf::Vector2i m_spriteSize;
	sf::Vector2f m_spriteScale;
	Direction m_direction;

	std::string m_animType;
	Animations m_animations;
	Anim_Base* m_animationCurrent;

	TextureManager* m_textureManager;
};