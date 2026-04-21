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
	Player* m_player;
	int m_hpUI = 0;
	int m_o2UI = 0;
};
