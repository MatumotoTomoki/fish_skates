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
	int m_sevolume = 5;
	int m_soundMode = 0;
	bool m_soundTest = false;
	int m_master = 10;
	int m_select;
private:
	SpriteRender m_sprite;
	SpriteRender m_backGround;
	FontRender m_font;
	FontRender m_menuFont;
	FontRender m_volumeFont;
	FontRender m_sevolumeFont;
	FontRender m_masterFont;
	Title* m_title;
	Game* m_game;
	SilenPengin* m_silenPengin;
	bool m_isPause = false;

	enum class PauseState {
		Main,   // 通常のメニュー選択
		Sound   // サウンド設定中
	};
	PauseState m_state = PauseState::Main;
	int m_volume = 5;
	
	
};

