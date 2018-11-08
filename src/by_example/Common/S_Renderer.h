#pragma once
#include "S_Base.h"
#include <SFML/Graphics.hpp>
#include <algorithm>
#include "Window.h"
#include "Direction.h"

class S_Renderer : public S_Base
{
public:
	S_Renderer(SystemManager* systemManager);
	~S_Renderer();

	void Update(float deltaTime) override;
	void HandleEvent(const EntityId& entity, const EntityEvent& event) override;
	void Notify(const Message& message) override;
	void Render(Window* window, unsigned int layer);

private:
	void SetSheetDirection(const EntityId& entity, const Direction& direction);
	void SortDrawables();
};

