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
	SpriteRender m_font;
	SpriteRender m_gauge;
	SpriteRender m_seafont;
	SpriteRender m_start;
	Game* m_game;
	Pause* m_pause;
	SoundSource* m_sound;
	bool m_flug = false;
	bool m_gaugeflug = false;
	bool m_startAlpha = false;
	float m_count = 3.0f;
	float m_scare = 0.0f;
	float m_alpha = 1.0f;
	float m_hamachiAlpha = 1.0f;
	float m_fontHaikei = 0.0f;
	float m_startColor = 1.0f;
	int m_i = 0;
	int m_j = 0;
	int m_newGame = 0;
	int m_se = 0;
	int m_3 = 0;
	int m_2 = 0;
	int m_1 = 0;
	int m_GO = 0;
	int m_sea = 0;
};
