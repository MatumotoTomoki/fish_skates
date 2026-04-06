#pragma once
class Game;
class Pause;
class Water;
class Title : public IGameObject
{
public:
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	SpriteRender m_render;
	FontRender m_font;
	FontRender m_seafont;
	Game* m_game;
	Pause* m_pause;
	bool m_flug = false;
	float m_count = 3.0f;
	int m_i = 0;
	int m_j = 0;
	int m_se = 0;

};

