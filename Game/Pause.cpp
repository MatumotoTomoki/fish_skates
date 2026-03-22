#include "stdafx.h"
#include "Pause.h"
#include "Title.h" 
#include "Game.h"
#include "SilenPengin.h"

bool Pause::Start() {
	m_sprite.Init("Assets/sprite/arrow.dds",150.0f,100.0f);
	m_backGround.Init("Assets/sprite/backGround.dds", 1920.0f, 1080.0f);
	Vector4 color = { 0.0f, 0.0f, 0.0f, 0.5f };
	m_backGround.SetMulColor(color);
	m_font.SetText(L"Pause");
	if (m_game) {
		m_game->SetBGMVolume(m_volume * 1.0f);
	}
	m_menuFont.SetText(L"メニューを閉じる\n\n\nサウンド設定\n\n\nタイトルに戻る\n\n\nゲームをやめる");
	m_menuFont.SetPosition(-260.0f, 250.0f, 0.0f);
	m_menuFont.SetScale(1.52f);
	m_font.SetPosition(-130.0f, 450.0f, 0.0f);
	m_font.SetScale(2.0f);
	m_title = FindGO<Title>("Title");
	m_sprite.Update();
	m_volumeFont.SetPosition(-220.0f, 155.0f, 0.0f);
	m_volumeFont.SetScale(2.0f);
	m_volumeFont.SetColor(1.0f,0.0f,0.0f,0.0f);
	m_sevolumeFont.SetPosition(-220.0f, 15.0f, 0.0f);
	m_sevolumeFont.SetScale(2.0f);
	m_sevolumeFont.SetColor(1.0f,0.0f,0.0f,0.0f);
	return true;
}

void Pause::Update() {
	if (g_pad[0]->IsTrigger(enButtonStart)) {
		m_soundMode = 0;
		m_font.SetText(L"Pause");
		m_font.SetPosition(-130.0f, 450.0f, 0.0f);
		m_menuFont.SetText(L"メニューを閉じる\n\n\nサウンド設定\n\n\nタイトルに戻る\n\n\nゲームをやめる");
		m_menuFont.SetPosition(-260.0f, 250.0f, 0.0f);
		m_state = PauseState::Main;
		m_isPause = !m_isPause;
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
					m_font.SetPosition(-290.0f, 450.0f, 0.0f);
					m_menuFont.SetText(L"BGM\n\nSE");
					m_menuFont.SetPosition(-350.0f, 150.0f, 0.0f);
					m_soundTest = true;
					break;
				case 3:
					m_isPause = !m_isPause;
					break;
				}
			}

			switch (m_mode) {
			case 0:
				m_sprite.SetPosition({ -300.0f,-360.0f,0.0f });
				break;
			case 1:
				m_sprite.SetPosition({ -300.0f,-170.0f,0.0f });
				break;
			case 2:
				m_sprite.SetPosition({ -300.0f,25.0f,0.0f });
				break;
			case 3:
				m_sprite.SetPosition({ -300.0f,220.0f,0.0f });
				break;
			}
		}
		else if (m_state == PauseState::Sound) {
			m_sprite.SetPosition({ -400.0f,120.0f,0.0f });
			if (g_pad[0]->IsTrigger(enButtonB)) { // Bボタンで戻る
				m_soundMode = 0;
				m_soundTest = false;
				m_font.SetText(L"Pause");
				m_font.SetPosition(-110.0f, 450.0f, 0.0f);
				m_menuFont.SetText(L"メニューを閉じる\n\n\nサウンド設定\n\n\nタイトルに戻る\n\n\nゲームをやめる");
				m_menuFont.SetPosition(-260.0f, 250.0f, 0.0f);
				m_state = PauseState::Main;
			}
			m_game = FindGO<Game>("Game");

			if (g_pad[0]->IsTrigger(enButtonUp)) {
				m_soundMode--;
				if (m_soundMode < 0) {
					m_soundMode = 1;
				}
			}
			if (g_pad[0]->IsTrigger(enButtonDown)) {
				m_soundMode++;
				if (m_soundMode > 1) {
					m_soundMode = 0;
				}
			}

			switch (m_soundMode) {
			case 0:
				m_sprite.SetPosition({ -400.0f,120.0f,0.0f }); // BGM
				break;
			case 1:
				m_sprite.SetPosition({ -400.0f,-5.0f,0.0f }); // SE
				break;
			}

			if (m_soundMode == 0) {
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
				m_silenPengin = FindGO<SilenPengin>("silenPengin");
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
		}
	}
	m_sprite.Update();
}

void Pause::Render(RenderContext& rc) {
	if (m_isPause == true) {
		m_backGround.Draw(rc);
		m_sprite.Draw(rc);
		m_font.Draw(rc);
		m_menuFont.Draw(rc);
		if (m_state == PauseState::Sound) {
			m_volumeFont.Draw(rc);
			m_sevolumeFont.Draw(rc);
		}
	}
}