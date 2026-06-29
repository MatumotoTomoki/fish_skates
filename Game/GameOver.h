#pragma once
class GameOver : public IGameObject
{
public:
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	SpriteRender m_render;
	SpriteRender m_nextRender;
	SoundSource* m_bgm;
	int m_i = 0;
	int m_gameoverState = 0;
	float m_color = 0.0f;
	float m_nextColor = 0.0f;
	bool m_change = false;
	bool m_flug = true;
};
