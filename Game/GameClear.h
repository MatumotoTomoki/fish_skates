#pragma once
class GameClear : public IGameObject
{
	bool Start();
    //更新処理。
    void Update();
    //描画処理。
    void Render(RenderContext& rc);
    //メンバ変数。
    SpriteRender m_spriteRender; //スプライトレンダ―。
};

