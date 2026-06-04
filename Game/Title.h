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
	SpriteRender m_manual;
	SpriteRender m_b;
	Game* m_game;
	Pause* m_pause;
	SoundSource* m_sound;
	bool m_flug = false;
	bool m_gaugeflug = false;
	bool m_startAlpha = false;
	bool m_coolTime = false;
	bool m_manualAlpha = false;
	bool m_optionState = false;
	bool m_optionMode = false;
	bool m_specialCamera = false;
	float m_count = 3.0f;
	float m_scare = 0.0f;
	float m_alpha = 1.0f;
	float m_hamachiAlpha = 1.0f;
	float m_fontHaikei = 0.0f;
	float m_startColor = 0.0f;
	float m_titleColor = 0.0f;
	float m_manualColor = 0.0f;
	float m_bColor = 0.0f;
	int m_i = 0;
	int m_j = 0;
	int m_newGame = 0;
	int m_se = 0;
	int m_3 = 0;
	int m_2 = 0;
	int m_1 = 0;
	int m_GO = 0;
	int m_sea = 0;
	int m_cool = 0;
	int m_optionSelecct = 0;
};
