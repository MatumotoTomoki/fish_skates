#pragma once
class Game;
class Title;
class Pause : public IGameObject
{
public:
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	bool IsPaused() const { return m_isPause; }
	int m_mode = 2;
	int m_volume = 10;
	int m_sevolume = 10;
	int m_soundMode = 0;
	int m_master = 7;
	int m_select;
	bool m_soundTest = false;
	bool m_return = false;
private:
	SpriteRender m_sprite;
	SpriteRender m_backGround;
	SpriteRender m_menuSprite;
	SpriteRender m_menuReturn;
	SpriteRender m_menuSound;
	SpriteRender m_returnTitle;
	SpriteRender m_endGame;
	SpriteRender m_soundBerSprite;
	SpriteRender m_seBerSprite;
	SpriteRender m_masterBerSprite;
	Game* m_game;
	Title* m_title;
	bool m_isPause = false;
	enum class PauseState {
		Main,   // 通常のメニュー選択
		Sound   // サウンド設定中
	};
	PauseState m_state = PauseState::Main;
};
