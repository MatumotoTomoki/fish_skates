#pragma once
class UI : public IGameObject
{
public:
	bool Start();
	void Update();
	void Render(RenderContext& rc);

private:
	SpriteRender m_spriteRender;
	SpriteRender m_spriteRender2;
	SpriteRender m_spriteRender3;
	SpriteRender m_spriteRender4;
	SpriteRender m_spriteRender5;
	FontRender m_fontRender;

	float m_o2 = -1.05f;

};

