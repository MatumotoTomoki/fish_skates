#include "stdafx.h"
#include "Pause.h"
#include "Title.h" 
#include "Game.h"
#include "SilenPengin.h"

bool Pause::Start() {
	m_sprite.Init("Assets/sprite/allow.dds",300.0f,200.0f);
	m_backGround.Init("Assets/sprite/backGround.dds", 1920.0f, 1080.0f);
	Vector4 color = { 0.0f, 0.0f, 0.0f, 0.5f };
	m_backGround.SetMulColor(color);
	m_font.SetText(L"ポーズ");
	if (m_game) {
		m_game->SetBGMVolume(m_volume * 1.0f);
	}
	m_menuFont.SetText(L"メニューを閉じる\n\n\nサウンド設定\n\n\nタイトルに戻る\n\n\nゲームをやめる");
	m_menuFont.SetPosition(-260.0f, 250.0f, 0.0f);
	m_menuFont.SetScale(1.52f);
	m_font.SetPosition(-150.0f, 450.0f, 0.0f);
	m_font.SetScale(2.0f);
	m_title = FindGO<Title>("Title");
	m_sprite.Update();
	m_volumeFont.SetPosition(-45.0f, 220.0f, 0.0f);
	m_volumeFont.SetScale(2.0f);
	m_volumeFont.SetColor(1.0f,0.0f,0.0f,0.0f);
	m_sevolumeFont.SetPosition(-45.0f, 60.0f, 0.0f);
	m_sevolumeFont.SetScale(2.0f);
	m_sevolumeFont.SetColor(1.0f,0.0f,0.0f,0.0f);
	m_masterFont.SetPosition(-45.0f, -100.0f, 0.0f);
	m_masterFont.SetScale(2.0f);
	m_masterFont.SetColor(1.0f, 0.0f, 0.0f, 0.0f);
	m_menuSprite.Init("Assets/sprite/menu.dds", 1920.0f, 1080.0f);
	//m_soundMenu.Init("Assets/sprite/soundMenu.dds", 1920.0f, 1080.0f);
	return true;
}

void Pause::Update() {
	if (m_game == nullptr) {
		m_game = FindGO<Game>("Game");
	}
	if (m_game) {
		if (g_pad[0]->IsTrigger(enButtonStart)) {
			m_soundMode = 0;
			m_font.SetText(L"ポーズ");
			m_font.SetPosition(-150.0f, 450.0f, 0.0f);
			m_menuFont.SetText(L"メニューを閉じる\n\n\nサウンド設定\n\n\nタイトルに戻る\n\n\nゲームをやめる");
			m_menuSprite.Init("Assets/sprite/menu.dds", 1920.0f, 1080.0f);
			m_menuFont.SetPosition(-260.0f, 250.0f, 0.0f);
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
						m_font.SetText(L"サウンド設定");
						m_font.SetPosition(-310.0f, 450.0f, 0.0f);
						m_menuFont.SetText(L"音楽\n\n\n効果音\n\n\nマスター\n\n\nメニューに戻る");
						m_menuSprite.Init("Assets/sprite/soundMenu.dds", 1920.0f, 1080.0f);
						m_menuFont.SetPosition(-260.0f, 245.0f, 0.0f);
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
					m_font.SetText(L"ポーズ");
					m_font.SetPosition(-150.0f, 450.0f, 0.0f);
					m_menuFont.SetText(L"メニューを閉じる\n\n\nサウンド設定\n\n\nタイトルに戻る\n\n\nゲームをやめる");
					m_menuSprite.Init("Assets/sprite/menu.dds", 1920.0f, 1080.0f);
					m_menuFont.SetPosition(-260.0f, 250.0f, 0.0f);
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
						m_font.SetText(L"ポーズ");
						m_font.SetPosition(-150.0f, 450.0f, 0.0f);
						m_menuFont.SetText(L"メニューを閉じる\n\n\nサウンド設定\n\n\nタイトルに戻る\n\n\nゲームをやめる");
						m_menuSprite.Init("Assets/sprite/menu.dds", 1920.0f, 1080.0f);
						m_menuFont.SetPosition(-260.0f, 250.0f, 0.0f);
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
				case 0:
					m_volumeFont.SetText(L"");
					break;
				case 1:
					m_volumeFont.SetText(L"l");
					break;
				case 2:
					m_volumeFont.SetText(L"ll");
					break;
				case 3:
					m_volumeFont.SetText(L"lll");
					break;
				case 4:
					m_volumeFont.SetText(L"llll");
					break;
				case 5:
					m_volumeFont.SetText(L"lllll");
					break;
				case 6:
					m_volumeFont.SetText(L"llllll");
					break;
				case 7:
					m_volumeFont.SetText(L"lllllll");
					break;
				case 8:
					m_volumeFont.SetText(L"llllllll");
					break;
				case 9:
					m_volumeFont.SetText(L"lllllllll");
					break;
				case 10:
					m_volumeFont.SetText(L"llllllllll");
					break;
				}

				switch (m_sevolume) {
				case 0:
					m_sevolumeFont.SetText(L"");
					break;
				case 1:
					m_sevolumeFont.SetText(L"l");
					break;
				case 2:
					m_sevolumeFont.SetText(L"ll");
					break;
				case 3:
					m_sevolumeFont.SetText(L"lll");
					break;
				case 4:
					m_sevolumeFont.SetText(L"llll");
					break;
				case 5:
					m_sevolumeFont.SetText(L"lllll");
					break;
				case 6:
					m_sevolumeFont.SetText(L"llllll");
					break;
				case 7:
					m_sevolumeFont.SetText(L"lllllll");
					break;
				case 8:
					m_sevolumeFont.SetText(L"llllllll");
					break;
				case 9:
					m_sevolumeFont.SetText(L"lllllllll");
					break;
				case 10:
					m_sevolumeFont.SetText(L"llllllllll");
					break;
				}

				switch (m_master) {
				case 0:
					m_masterFont.SetText(L"");
					break;
				case 1:
					m_masterFont.SetText(L"l");
					break;
				case 2:
					m_masterFont.SetText(L"ll");
					break;
				case 3:
					m_masterFont.SetText(L"lll");
					break;
				case 4:
					m_masterFont.SetText(L"llll");
					break;
				case 5:
					m_masterFont.SetText(L"lllll");
					break;
				case 6:
					m_masterFont.SetText(L"llllll");
					break;
				case 7:
					m_masterFont.SetText(L"lllllll");
					break;
				case 8:
					m_masterFont.SetText(L"llllllll");
					break;
				case 9:
					m_masterFont.SetText(L"lllllllll");
					break;
				case 10:
					m_masterFont.SetText(L"llllllllll");
					break;
				}
			}
		}
		m_sprite.Update();
	}
}

void Pause::Render(RenderContext& rc) {
	if (m_isPause == true) {
		m_backGround.Draw(rc);
		m_sprite.Draw(rc);
		m_font.Draw(rc);
		//m_menuFont.Draw(rc);
		m_menuSprite.Draw(rc);
		if (m_state == PauseState::Sound) {
			m_masterMenu.Draw(rc);
			//m_soundMenu.Draw(rc);
			m_volumeFont.Draw(rc);
			m_sevolumeFont.Draw(rc);
			m_masterFont.Draw(rc);
		}
	}
}
