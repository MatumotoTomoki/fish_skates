#pragma once
class Game;
class GameClear;
class GameOver;
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
	SpriteRender m_pauseSound;
	SpriteRender m_menuSound2;
	SpriteRender m_menuSE;
	SpriteRender m_menuMaster;
	SpriteRender m_returnMenu;
	SpriteRender m_soundBerSprite;
	SpriteRender m_seBerSprite;
	SpriteRender m_masterBerSprite;
	SpriteRender m_defalt;
	Game* m_game;
	GameClear* m_gameClear;
	GameOver* m_gameOver;
	Title* m_title;
	bool m_isPause = false;
	enum class PauseState {
		Main,   // 通常のメニュー選択
		Sound   // サウンド設定中
	};
	PauseState m_state = PauseState::Main;
};
