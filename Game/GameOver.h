#pragma once
class GameOver : public IGameObject
{
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	SpriteRender m_render;
	SoundSource* m_bgm;
	int m_i = 0;
	float m_color = 0.0f;
	bool m_change = false;
};

