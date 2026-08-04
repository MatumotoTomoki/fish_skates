#pragma once
class Player;
class UI : public IGameObject
{
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	SpriteRender m_spriteRender;
	SpriteRender m_spriteRender2;
	SpriteRender m_spriteRender3;
	SpriteRender m_spriteRender4;
	SpriteRender m_spriteRender5;
	SpriteRender m_startRender;
	SpriteRender m_warningRender;
	SpriteRender m_countRender;
	FontRender m_font;
	FontRender m_getafont;
	FontRender m_speedfont;
	Player* m_player;
	int m_hpUI = 0;
	int m_o2UI = 0;
	int m_secount = 0;
	int m_number = 2;
	bool m_warningFlag = false;
	bool m_heal = false;
	bool m_se = false;
	bool m_color = false;
	bool m_color1 = false;
	bool m_color2 = false;
	float m_alpha = 1.0f;
	float m_posColor = 0.0f;
	float m_posColor1 = 1.0f;
	float m_posColor2 = 0.5f;
	float m_countDown = 3.0f;
};
