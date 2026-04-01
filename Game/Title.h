#pragma once
class Game;
class Pause;
class Title : public IGameObject
{
public:
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	SpriteRender m_render;
	FontRender m_font;
	Game* m_game;
	Pause* m_pause;
	bool m_flug = false;
	float m_count = 3.0f;

};

