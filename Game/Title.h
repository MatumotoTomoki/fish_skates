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
	SpriteRender m_font;
	SpriteRender m_gauge;
	FontRender m_seafont;
	Game* m_game;
	Pause* m_pause;
	bool m_flug = false;
	bool m_gaugeflug = false;
	float m_count = 3.0f;
	float m_scare = 0.0f;
	int m_i = 0;
	int m_j = 0;
	int m_se = 0;
	int m_3 = 0;
	int m_2 = 0;
	int m_1 = 0;
	int m_GO = 0;
	int m_sea = 0;

};

