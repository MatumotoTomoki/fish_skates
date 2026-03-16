#pragma once
class Title;
class Game;
class Pause : public IGameObject
{
public:
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	bool IsPaused() const { return m_isPause; }

	int m_mode = 2;
private:
	SpriteRender m_sprite;
	SpriteRender m_backGround;
	FontRender m_font;
	FontRender m_menuFont;
	FontRender m_volumeFont;
	Title* m_title;
	Game* m_game;
	bool m_isPause = false;

	enum class PauseState {
		Main,   // 通常のメニュー選択
		Sound   // サウンド設定中
	};
	PauseState m_state = PauseState::Main;
	int m_volume = 5;
};

