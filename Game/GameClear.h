#pragma once
class GameClear : public IGameObject
{
	bool Start();
    void Update();
    void Render(RenderContext& rc);
    SpriteRender m_spriteRender;
};

