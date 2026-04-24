#pragma once
class GameClear : public IGameObject
{
	bool Start();
    void Update();
    void Render(RenderContext& rc);
    SpriteRender m_spriteRender;
    SoundSource* m_bgm;
    int m_i = 0;
    float m_color = 0.0f;
    bool m_change = false;
};

