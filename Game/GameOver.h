#pragma once
class GameOver : public IGameObject
{
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	SpriteRender m_render;
	SoundSource* m_bgm;
};

