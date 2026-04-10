#include "stdafx.h"
#include "Pause.h"
#include "Title.h" 
#include "Game.h"
#include "SilenPengin.h"

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
		m_game->SetBGMVolume(m_volume * 1.0f);
	}
	m_title = FindGO<Title>("Title");
	m_sprite.Update();
	m_menuSprite.Init("Assets/sprite/menu.dds", 1920.0f, 1080.0f);
	m_soundBerSprite.Update();
	m_seBerSprite.Update();
	m_masterBerSprite.Update();
	return true;
}

void Pause::Update() {
	if (m_game == nullptr) {
		m_game = FindGO<Game>("Game");
	}
	if (m_game != nullptr and m_game->m_initialized == false) {
		return;
	}
	if (m_game) {
		if (g_pad[0]->IsTrigger(enButtonStart)) {
			m_soundMode = 0;
			m_menuSprite.Init("Assets/sprite/menu.dds", 1920.0f, 1080.0f);
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
				if (g_pad[0]->IsTrigger(enButtonA)) {
					switch (m_mode) {
					case 0:
						PostQuitMessage(0);
						break;
					case 1:
						m_title = NewGO<Title>(0, "Title");
						DeleteGO(this);
						break;
					case 2:
						m_state = PauseState::Sound;
						m_menuSprite.Init("Assets/sprite/soundMenu.dds", 1920.0f, 1080.0f);
						break;
					case 3:
						m_isPause = !m_isPause;
						break;
					}
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
					m_menuSprite.Init("Assets/sprite/menu.dds", 1920.0f, 1080.0f);
					m_state = PauseState::Main;
				}
				m_game = FindGO<Game>("Game");

				if (g_pad[0]->IsTrigger(enButtonUp)) {
					m_soundMode--;
					if (m_soundMode < 0) {
						m_soundMode = 3;
					}
				}
				if (g_pad[0]->IsTrigger(enButtonDown)) {
					m_soundMode++;
					if (m_soundMode > 3) {
						m_soundMode = 0;
					}
				}

				switch (m_soundMode) {
				case 0:
					m_sprite.SetPosition({ -480.0f,190.0f,0.0f }); // BGM
					break;
				case 1:
					m_sprite.SetPosition({ -480.0f,25.0f,0.0f }); // SE
					break;
				case 2:
					m_sprite.SetPosition({ -480.0f,-130.0f,0.0f }); // マスター
					break;
				case 3:
					m_sprite.SetPosition({ -480.0f,-300.0f,0.0f }); //メニューに戻る
					break;
				}

				if (m_soundMode == 0) {
					m_select = m_volume;
					if (g_pad[0]->IsTrigger(enButtonLeft)) {
						m_volume = max(0, m_volume - 1);
						if (m_game) {
							// m_volume(0~10) を 0.0f ~ 1.0f に変換して適用
							m_game->SetBGMVolume(m_volume * 1.0f);
						}
					}


					if (g_pad[0]->IsTrigger(enButtonRight)) {
						m_volume = min(10, m_volume + 1);
						if (m_game) {
							// m_volume(0~10) を 0.0f ~ 1.0f に変換して適用
							m_game->SetBGMVolume(m_volume * 1.0f);
						}
					}
				}

				if (m_soundMode == 1) {
					m_select = m_sevolume;
					m_silenPengin = FindGO<SilenPengin>("SilenPengin");
					if (g_pad[0]->IsTrigger(enButtonLeft))
					{
						m_sevolume = max(0, m_sevolume - 1);
						if (m_silenPengin)
						{
							m_silenPengin->SetSEVolume(m_sevolume * 1.0f);
						}
					}

					if (g_pad[0]->IsTrigger(enButtonRight))
					{
						m_sevolume = min(10, m_sevolume + 1);
						if (m_silenPengin)
						{
							m_silenPengin->SetSEVolume(m_sevolume * 1.0f);
						}
					}
				}

				if (m_soundMode == 2) {
					m_select = m_master;
					m_silenPengin = FindGO<SilenPengin>("SilenPengin");
					if (g_pad[0]->IsTrigger(enButtonLeft)) {
						m_master = max(0, m_master - 1);
					}
					if (g_pad[0]->IsTrigger(enButtonRight)) {
						m_master = min(10, m_master + 1);
					}
				}

				if (m_soundMode == 3) {
					if (g_pad[0]->IsTrigger(enButtonA)) {
						m_menuSprite.Init("Assets/sprite/menu.dds", 1920.0f, 1080.0f);
						m_state = PauseState::Main;
					}
				}

				// BGMに反映
				if (m_game) {
					float finalBGM = (m_volume / 10.0f) * (m_master / 10.0f);
					m_game->SetBGMVolume(finalBGM);
				}

				// SEに反映
				if (m_silenPengin) {
					float finalSE = (m_sevolume / 10.0f) * (m_master / 10.0f);
					m_silenPengin->SetSEVolume(finalSE);
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
	}
}

void Pause::Render(RenderContext& rc) {
	if (m_isPause == true) {
		m_backGround.Draw(rc);
		m_sprite.Draw(rc);
		m_menuSprite.Draw(rc);
		if (m_state == PauseState::Sound) {
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
