#pragma once
class Title;
class Game;
class SilenPengin;
class Pause : public IGameObject
{
public:
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	bool IsPaused() const { return m_isPause; }

	int m_mode = 2;
	int m_sevolume = 10;
	int m_soundMode = 0;
	bool m_soundTest = false;
	int m_master = 7;
	int m_select;
private:
	SpriteRender m_sprite;
	SpriteRender m_backGround;
	SpriteRender m_menuSprite;
	SpriteRender m_soundBerSprite;
	SpriteRender m_seBerSprite;
	SpriteRender m_masterBerSprite;
	Title* m_title;
	Game* m_game;
	SilenPengin* m_silenPengin;
	bool m_isPause = false;
	enum class PauseState {
		Main,   // 通常のメニュー選択
		Sound   // サウンド設定中
	};
	PauseState m_state = PauseState::Main;
	int m_volume = 10;
};
