#include "stdafx.h"
#include "Pause.h"
#include "Title.h" 
#include "Game.h"
#include "GameClear.h"
#include "GameOver.h"
#include "Player.h"

bool Pause::Start() {
	m_sprite.Init("Assets/sprite/allow.dds", 300.0f, 200.0f);
	m_backGround.Init("Assets/sprite/backGround.dds", 1920.0f, 1080.0f);
	m_soundBerSprite.Init("Assets/sprite/bar10.dds", 500.0f, 150.0f);
	m_seBerSprite.Init("Assets/sprite/bar10.dds", 500.0f, 150.0f);
	m_masterBerSprite.Init("Assets/sprite/bar7.dds", 500.0f, 150.0f);
	m_soundBerSprite.SetPosition({ 210.0f,180.0f,0.0f });
	m_seBerSprite.SetPosition({ 210.0f,20.0f,0.0f });
	m_masterBerSprite.SetPosition({ 210.0f,-140.0f,0.0f });
	Vector4 color = { 0.0f, 0.0f, 0.0f, 0.5f };
	m_backGround.SetMulColor(color);
	if (m_game) {
		auto bgm = m_game->GetCurrentBGM();
		if (bgm) {
			float finalBGM = (m_volume / 10.0f) * (m_master / 10.0f);
			bgm->SetVolume(finalBGM);
		}
	}
	m_sprite.Update();
	m_menuSprite.Init("Assets/sprite/pause.dds", 1920.0f, 1080.0f);
	m_menuReturn.Init("Assets/sprite/returnManu.dds", 1920.0f, 1080.0f);
	m_menuSound.Init("Assets/sprite/soundTest.dds", 1920.0f, 1080.0f);
	m_returnTitle.Init("Assets/sprite/returnTitle.dds", 1920.0f, 1080.0f);
	m_endGame.Init("Assets/sprite/endGame.dds", 1920.0f, 1080.0f);
	m_pauseSound.Init("Assets/sprite/soundPauseMenu.dds", 1920.0f, 1080.0f);
	m_menuSound2.Init("Assets/sprite/soundMove.dds", 1920.0f, 1080.0f);
	m_menuSE.Init("Assets/sprite/seMove.dds", 1920.0f, 1080.0f);
	m_menuMaster.Init("Assets/sprite/masterMove.dds", 1920.0f, 1080.0f);
	m_returnMenu.Init("Assets/sprite/returnMove.dds", 1920.0f, 1080.0f);
	m_defalt.Init("Assets/sprite/defalt.dds", 700.0f, 500.0f);
	m_defalt.SetPosition({ -200.0f,-300.0f,0.0f });
	m_returnMenu.SetPosition({ 0.0f,-140.0f,0.0f });
	m_soundBerSprite.Update();
	m_seBerSprite.Update();
	m_masterBerSprite.Update();
	m_defalt.Update();
	return true;
}

void Pause::Update() {
	if (m_game == nullptr) {
		m_game = FindGO<Game>("Game");
	}
	if (m_gameClear == nullptr) {
		m_gameClear = FindGO<GameClear>("GameClear");
	}
	if (m_gameOver == nullptr) {
		m_gameOver = FindGO<GameOver>("GameOver");
	}
	if (m_title == nullptr) {
		m_title = FindGO<Title>("Title");
	}
	if (m_player == nullptr) {
		m_player = FindGO<Player>("Player");
	}
	if (m_title) {
		m_player = nullptr;
		m_title = nullptr;
		return;
	}
	if (m_gameClear) {
		m_gameClear = nullptr;
		return;
	}
	if (m_gameOver) {
		m_gameOver = nullptr;
		return;
	}
	if (m_player->m_start == true) {
		if (g_pad[0]->IsTrigger(enButtonStart)) {
			m_soundMode = 0;
			m_menuSprite.Init("Assets/sprite/pause.dds", 1920.0f, 1080.0f);
			m_menuReturn.Init("Assets/sprite/returnMenu.dds", 1920.0f, 1080.0f);
			m_menuSound.Init("Assets/sprite/soundTest.dds", 1920.0f, 1080.0f);
			m_returnTitle.Init("Assets/sprite/returnTitle.dds", 1920.0f, 1080.0f);
			m_endGame.Init("Assets/sprite/endGame.dds", 1920.0f, 1080.0f);
			m_state = PauseState::Main;
			m_isPause = !m_isPause;
			m_soundTest = false;
			m_mode = 3;
		}
		if (m_isPause == true) {
			if (m_state == PauseState::Main) {
				if (g_pad[0]->IsTrigger(enButtonUp)) {
					m_mode++;
					if (m_mode > 3) {
						m_mode = 0;
					}
				}
				if (g_pad[0]->IsTrigger(enButtonDown)) {
					m_mode--;
					if (m_mode < 0) {
						m_mode = 3;
					}
				}
				switch (m_mode) {
				case 0:
					if (g_pad[0]->IsTrigger(enButtonA)) {
						PostQuitMessage(0);
					}
					m_menuReturn.SetScale({ 1.0f,1.0f,1.0f });
					m_menuSound.SetScale({ 1.0f,1.0f,1.0f });
					m_returnTitle.SetScale({ 1.0f,1.0f,1.0f });
					m_endGame.SetScale({ 1.05f,1.05f,1.0f });
					break;
				case 1:
					if (g_pad[0]->IsTrigger(enButtonA)) {
						NewGO<Title>(0, "Title");
						m_isPause = false;
						m_return = true;
					}
					m_menuReturn.SetScale({ 1.0f,1.0f,1.0f });
					m_menuSound.SetScale({ 1.0f,1.0f,1.0f });
					m_returnTitle.SetScale({ 1.05f,1.05f,1.0f });
					m_endGame.SetScale({ 1.0f,1.0f,1.0f });
					break;
				case 2:
					if (g_pad[0]->IsTrigger(enButtonA)) {
						m_state = PauseState::Sound;
					}
					m_menuReturn.SetScale({ 1.0f,1.0f,1.0f });
					m_menuSound.SetScale({ 1.05f,1.05f,1.0f });
					m_returnTitle.SetScale({ 1.0f,1.0f,1.0f });
					m_endGame.SetScale({ 1.0f,1.0f,1.0f });
					break;
				case 3:
					if (g_pad[0]->IsTrigger(enButtonA)) {
						m_isPause = !m_isPause;
					}
					m_menuReturn.SetScale({ 1.05f,1.05f,1.0f });
					m_menuSound.SetScale({ 1.0f,1.0f,1.0f });
					m_returnTitle.SetScale({ 1.0f,1.0f,1.0f });
					m_endGame.SetScale({ 1.0f,1.0f,1.0f });
					break;
				}

				switch (m_mode) {
				case 0:
					m_sprite.SetPosition({ -400.0f,-310.0f,0.0f });
					break;
				case 1:
					m_sprite.SetPosition({ -400.0f,-150.0f,0.0f });
					break;
				case 2:
					m_sprite.SetPosition({ -400.0f,25.0f,0.0f });
					break;
				case 3:
					m_sprite.SetPosition({ -470.0f,200.0f,0.0f });
					break;
				}
			}
			else if (m_state == PauseState::Sound) {
				m_sprite.SetPosition({ -900.0f,120.0f,0.0f });
				if (g_pad[0]->IsTrigger(enButtonB)) { // Bボタンで戻る
					m_soundMode = 0;
					m_menuSprite.Init("Assets/sprite/pause.dds", 1920.0f, 1080.0f);
					m_state = PauseState::Main;
				}
				m_game = FindGO<Game>("Game");
				if (g_pad[0]->IsTrigger(enButtonUp)) {
					m_soundMode--;
					if (m_soundMode < 0) {
						m_soundMode = 4;
					}
				}
				if (g_pad[0]->IsTrigger(enButtonDown)) {
					m_soundMode++;
					if (m_soundMode > 4) {
						m_soundMode = 0;
					}
				}
				switch (m_soundMode) {
				case 0:
					m_sprite.SetPosition({ -480.0f,190.0f,0.0f }); // BGM
					m_menuSound2.SetScale({ 1.05f,1.05f,1.0f });
					m_menuSE.SetScale({ 1.0f,1.0f,1.0f });
					m_menuMaster.SetScale({ 1.0f,1.0f,1.0f });
					m_returnMenu.SetScale({ 1.0f,1.0f,1.0f });
					m_defalt.SetScale({ 1.0f,1.0f,1.0f });
					break;
				case 1:
					m_sprite.SetPosition({ -480.0f,25.0f,0.0f }); // SE
					m_menuSound2.SetScale({ 1.0f,1.0f,1.0f });
					m_menuSE.SetScale({ 1.05f,1.05f,1.0f });
					m_menuMaster.SetScale({ 1.0f,1.0f,1.0f });
					m_returnMenu.SetScale({ 1.0f,1.0f,1.0f });
					m_defalt.SetScale({ 1.0f,1.0f,1.0f });
					break;
				case 2:
					m_sprite.SetPosition({ -480.0f,-130.0f,0.0f }); // マスター
					m_menuSound2.SetScale({ 1.0f,1.0f,1.0f });
					m_menuSE.SetScale({ 1.0f,1.0f,1.0f });
					m_menuMaster.SetScale({ 1.05f,1.05f,1.0f });
					m_returnMenu.SetScale({ 1.0f,1.0f,1.0f });
					m_defalt.SetScale({ 1.0f,1.0f,1.0f });
					break;
				case 3:
					m_sprite.SetPosition({ -480.0f,-290.0f,0.0f }); //メニューに戻る
					m_menuSound2.SetScale({ 1.0f,1.0f,1.0f });
					m_menuSE.SetScale({ 1.0f,1.0f,1.0f });
					m_menuMaster.SetScale({ 1.0f,1.0f,1.0f });
					m_returnMenu.SetScale({ 1.0f,1.0f,1.0f });
					m_defalt.SetScale({ 1.05f,1.05f,1.0f });
					break;
				case 4:
					m_sprite.SetPosition({ -480.0f,-440.0f,0.0f }); //メニューに戻る
					m_menuSound2.SetScale({ 1.0f,1.0f,1.0f });
					m_menuSE.SetScale({ 1.0f,1.0f,1.0f });
					m_menuMaster.SetScale({ 1.0f,1.0f,1.0f });
					m_returnMenu.SetScale({ 1.05f,1.05f,1.0f });
					m_defalt.SetScale({ 1.0f,1.0f,1.0f });
					break;
				}
				if (m_soundMode == 0) {
					m_select = m_volume;
					if (g_pad[0]->IsTrigger(enButtonLeft)) {
						m_volume = max(0, m_volume - 1);
						if (m_game) {
							auto bgm = m_game->GetCurrentBGM();
							if (bgm) {
								float finalBGM = (m_volume / 10.0f) * (m_master / 10.0f);
								bgm->SetVolume(finalBGM);
							}
						}
					}
					if (g_pad[0]->IsTrigger(enButtonRight)) {
						m_volume = min(10, m_volume + 1);
						if (m_game) {
							auto bgm = m_game->GetCurrentBGM();
							if (bgm) {
								float finalBGM = (m_volume / 10.0f) * (m_master / 10.0f);
								bgm->SetVolume(finalBGM);
							}
						}
					}
				}
				if (m_soundMode == 1) {
					m_select = m_sevolume;
					if (g_pad[0]->IsTrigger(enButtonLeft)) {
						m_sevolume = max(0, m_sevolume - 1);
					}
					if (g_pad[0]->IsTrigger(enButtonRight)) {
						m_sevolume = min(10, m_sevolume + 1);
					}
				}
				if (m_soundMode == 2) {
					m_select = m_master;
					if (g_pad[0]->IsTrigger(enButtonLeft)) {
						m_master = max(0, m_master - 1);
					}
					if (g_pad[0]->IsTrigger(enButtonRight)) {
						m_master = min(10, m_master + 1);
					}
				}
				if (m_soundMode == 3) {
					if (g_pad[0]->IsTrigger(enButtonA)) {
						m_volume = 10;
						m_sevolume = 10;
						m_master = 7;
					}
				}
				if (m_soundMode == 4) {
					if (g_pad[0]->IsTrigger(enButtonA)) {
						m_soundMode = 0;
						m_menuSprite.Init("Assets/sprite/pause.dds", 1920.0f, 1080.0f);
						m_state = PauseState::Main;
					}
				}
				// BGMに反映
				if (m_game) {
					auto bgm = m_game->GetCurrentBGM();
					if (bgm) {
						float finalBGM = (m_volume / 10.0f) * (m_master / 10.0f);
						bgm->SetVolume(finalBGM);
					}
				}
				switch (m_volume) {
				case 1:
					m_soundBerSprite.Init("Assets/sprite/bar1.dds", 500.0f, 150.0f);
					break;
				case 2:
					m_soundBerSprite.Init("Assets/sprite/bar2.dds", 500.0f, 150.0f);
					break;
				case 3:
					m_soundBerSprite.Init("Assets/sprite/bar3.dds", 500.0f, 150.0f);
					break;
				case 4:
					m_soundBerSprite.Init("Assets/sprite/bar4.dds", 500.0f, 150.0f);
					break;
				case 5:
					m_soundBerSprite.Init("Assets/sprite/bar5.dds", 500.0f, 150.0f);
					break;
				case 6:
					m_soundBerSprite.Init("Assets/sprite/bar6.dds", 500.0f, 150.0f);
					break;
				case 7:
					m_soundBerSprite.Init("Assets/sprite/bar7.dds", 500.0f, 150.0f);
					break;
				case 8:
					m_soundBerSprite.Init("Assets/sprite/bar8.dds", 500.0f, 150.0f);
					break;
				case 9:
					m_soundBerSprite.Init("Assets/sprite/bar9.dds", 500.0f, 150.0f);
					break;
				case 10:
					m_soundBerSprite.Init("Assets/sprite/bar10.dds", 500.0f, 150.0f);
					break;
				}
				switch (m_sevolume) {
				case 1:
					m_seBerSprite.Init("Assets/sprite/bar1.dds", 500.0f, 150.0f);
					break;
				case 2:
					m_seBerSprite.Init("Assets/sprite/bar2.dds", 500.0f, 150.0f);
					break;
				case 3:
					m_seBerSprite.Init("Assets/sprite/bar3.dds", 500.0f, 150.0f);
					break;
				case 4:
					m_seBerSprite.Init("Assets/sprite/bar4.dds", 500.0f, 150.0f);
					break;
				case 5:
					m_seBerSprite.Init("Assets/sprite/bar5.dds", 500.0f, 150.0f);
					break;
				case 6:
					m_seBerSprite.Init("Assets/sprite/bar6.dds", 500.0f, 150.0f);
					break;
				case 7:
					m_seBerSprite.Init("Assets/sprite/bar7.dds", 500.0f, 150.0f);
					break;
				case 8:
					m_seBerSprite.Init("Assets/sprite/bar8.dds", 500.0f, 150.0f);
					break;
				case 9:
					m_seBerSprite.Init("Assets/sprite/bar9.dds", 500.0f, 150.0f);
					break;
				case 10:
					m_seBerSprite.Init("Assets/sprite/bar10.dds", 500.0f, 150.0f);
					break;
				}
				switch (m_master) {
				case 1:
					m_masterBerSprite.Init("Assets/sprite/bar1.dds", 500.0f, 150.0f);
					break;
				case 2:
					m_masterBerSprite.Init("Assets/sprite/bar2.dds", 500.0f, 150.0f);
					break;
				case 3:
					m_masterBerSprite.Init("Assets/sprite/bar3.dds", 500.0f, 150.0f);
					break;
				case 4:
					m_masterBerSprite.Init("Assets/sprite/bar4.dds", 500.0f, 150.0f);
					break;
				case 5:
					m_masterBerSprite.Init("Assets/sprite/bar5.dds", 500.0f, 150.0f);
					break;
				case 6:
					m_masterBerSprite.Init("Assets/sprite/bar6.dds", 500.0f, 150.0f);
					break;
				case 7:
					m_masterBerSprite.Init("Assets/sprite/bar7.dds", 500.0f, 150.0f);
					break;
				case 8:
					m_masterBerSprite.Init("Assets/sprite/bar8.dds", 500.0f, 150.0f);
					break;
				case 9:
					m_masterBerSprite.Init("Assets/sprite/bar9.dds", 500.0f, 150.0f);
					break;
				case 10:
					m_masterBerSprite.Init("Assets/sprite/bar10.dds", 500.0f, 150.0f);
					break;
				}
			}
		}
		m_sprite.Update();
		m_soundBerSprite.Update();
		m_menuReturn.Update();
		m_menuSound.Update();
		m_returnTitle.Update();
		m_endGame.Update();
		m_pauseSound.Update();
		m_menuSound2.Update();
		m_menuSE.Update();
		m_menuMaster.Update();
		m_returnMenu.Update();
		m_defalt.Update();
	}
}

void Pause::Render(RenderContext& rc) {
	if (m_isPause == true) {
		m_backGround.Draw(rc);
		m_sprite.Draw(rc);
		if (m_state == PauseState::Main) {
			m_menuSprite.Draw(rc);
			m_menuReturn.Draw(rc);
			m_menuSound.Draw(rc);
			m_returnTitle.Draw(rc);
			m_endGame.Draw(rc);
		}
		if (m_state == PauseState::Sound) {
			m_pauseSound.Draw(rc);
			m_menuSound2.Draw(rc);
			m_menuSE.Draw(rc);
			m_menuMaster.Draw(rc);
			m_returnMenu.Draw(rc);
			m_defalt.Draw(rc);
			if (m_volume != 0) {
				m_soundBerSprite.Draw(rc);
			}
			if (m_sevolume != 0) {
				m_seBerSprite.Draw(rc);
			}
			if (m_master != 0) {
				m_masterBerSprite.Draw(rc);
			}
		}
	}
}
