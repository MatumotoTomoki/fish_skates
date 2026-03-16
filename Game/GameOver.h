#pragma once
class Title;
class GameOver : public IGameObject
{
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	SpriteRender m_render;
	Title* m_title;
};

