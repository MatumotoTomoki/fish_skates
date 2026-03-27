#pragma once
class Game;
class Title : public IGameObject
{
public:
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	SpriteRender m_render;
	FontRender m_font;
	Game* m_game;
	bool m_flug = false;
	float m_count = 3.0f;

};

