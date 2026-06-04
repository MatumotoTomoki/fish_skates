#include "stdafx.h"
#include "Title.h"
#include "Game.h"
#include "Pause.h"
#include "Water.h"
#include "GameCamera.h"

bool Title::Start() {
	m_render.Init("Assets/sprite/title.dds", 1920.0f, 1080.0f);
	m_manual.Init("Assets/sprite/Manual.dds", 1920.0f, 1080.0f);
	m_b.Init("Assets/sprite/a.DDS", 1000.0f, 700.0f);
	m_b.SetPosition({ 750.0f,-450.0f,0.0f });
	m_b.SetScale({ 0.5f,0.5f,1.0f });
	m_b.Update();
	g_soundEngine->ResistWaveFileBank(2, "Assets/Sound/start.wav");
	g_soundEngine->ResistWaveFileBank(8, "Assets/Sound/countdown.wav");
	g_soundEngine->ResistWaveFileBank(11, "Assets/sound/title.wav");
	g_soundEngine->ResistWaveFileBank(12, "Assets/sound/ok.wav");
	g_soundEngine->ResistWaveFileBank(13, "Assets/sound/cancel.wav");
	g_soundEngine->ResistWaveFileBank(20, "Assets/sound/select.wav");
	m_sound = NewGO<SoundSource>(0);
	m_sound->Init(11);
	m_sound->Play(true);
	m_pause = FindGO<Pause>("Pause");
	float finalSE = (m_bgmVol / 10.0f) * (m_masVol / 10.0f);
	m_sound->SetVolume(finalSE);
	m_font.Init("Assets/sprite/Gaugeflame.dds", 1600.0f, 200.0f);
	m_gauge.Init("Assets/sprite/Gauge.dds", 1600.0f, 200.0f);
	m_seafont.Init("Assets/sprite/sea.dds", 600.0f, 400.0f);
	m_seafont.SetPosition({ 10.0f, -200.0f, 0.0f });
	m_start.Init("Assets/sprite/next.dds", 1000.0f, 700.0f);
	m_start.SetPosition({ 0.0f,-300.0f,0.0f });
	m_font.SetPosition({ 0.0f, 0.0f, 0.0f });
	m_gauge.SetPosition({ -600.0f, -7.0f, 0.0f });
	m_gauge.SetPivot({ 0.13f,0.5f });
	m_gauge.SetScale({ -1600.0f,200.0f,0.0f });
	m_gauge.Update();
	m_seafont.Update();
	m_start.Update();
	m_manual.Update();
	return true;
}

void Title::Update() {
	Vector4 titleColor = { 1.0f,1.0f,1.0f,m_titleColor };
	m_titleColor += 0.01f;
	m_render.SetMulColor(titleColor);
	Vector4 startColor = { 1.0f, 1.0f, 1.0f, m_startColor };
	if (m_startColor >= 1.0f) {
		m_startAlpha = false;
	}
	if (m_startColor <= 0.0f) {
		m_startAlpha = true;
	}
	if (m_startAlpha == false) {
		m_startColor -= 0.01f;
	}
	if (m_startAlpha == true) {
		m_startColor += 0.01f;
	}
	m_start.SetMulColor(startColor);
	if (g_pad[0]->IsTrigger(enButtonRight) or g_pad[0]->IsTrigger(enButtonLeft)) {
		if (m_optionMode == false) {
			m_optionState = !m_optionState;
			SoundSource* se = NewGO<SoundSource>(0);
			se->Init(20);
			se->Play(false);
			float finalSE = (m_seVol / 10.0f) * (m_masVol / 10.0f);
			se->SetVolume(finalSE);
		}
	}
	if (m_coolTime == false) {
		float finalBGM = (m_bgmVol / 10.0f) * (m_masVol / 10.0f);
		m_sound->SetVolume(finalBGM);
	}
	if (g_pad[0]->IsTrigger(enButtonA) and m_j == 0 and m_optionState == false) {
		m_start.Init("Assets/sprite/start.dds", 1000.0f, 700.0f);
		m_titleColor = 1.0f;
		DeleteGO(m_sound);
		m_j++;
		SoundSource* se = NewGO<SoundSource>(0);
		se->Init(12);
		se->Play(false);
		float finalSE = (m_seVol / 10.0f) * (m_masVol / 10.0f);
		se->SetVolume(finalSE);
		m_coolTime = true;
	}
	//設定に移行する処理
	if (m_optionState == true and m_optionMode == false and g_pad[0]->IsTrigger(enButtonA)) {
		m_render.Init("Assets/sprite/hamachi.dds", 1920.0f, 1080.0f);
		SoundSource* se = NewGO<SoundSource>(0);
		se->Init(12);
		se->Play(false);
		float finalSE = (m_seVol / 10.0f) * (m_masVol / 10.0f);
		se->SetVolume(finalSE);
		m_optionMode = true;
	}
	if (m_optionMode == true and g_pad[0]->IsTrigger(enButtonB)) {
		m_render.Init("Assets/sprite/title.dds", 1920.0f, 1080.0f);
		SoundSource* se = NewGO<SoundSource>(0);
		se->Init(13);
		se->Play(false);
		float finalSE = (m_seVol / 10.0f) * (m_masVol / 10.0f);
		se->SetVolume(finalSE);
		m_optionMode = false;
		m_optionSelecct = 0;
	}
	//オプションの項目選択
	if (m_optionMode == true) {
		if (g_pad[0]->IsTrigger(enButtonUp)) {
			SoundSource* se = NewGO<SoundSource>(0);
			se->Init(20);
			se->Play(false);
			float finalSE = (m_seVol / 10.0f) * (m_masVol / 10.0f);
			se->SetVolume(finalSE);
			if (m_optionSelecct != 0) {
				m_optionSelecct--;
			}
			else {
				m_optionSelecct = 5;
			}
		}
		if (g_pad[0]->IsTrigger(enButtonDown)) {
			SoundSource* se = NewGO<SoundSource>(0);
			se->Init(20);
			se->Play(false);
			float finalSE = (m_seVol / 10.0f) * (m_masVol / 10.0f);
			se->SetVolume(finalSE);
			if (m_optionSelecct != 5) {
				m_optionSelecct++;
			}
			else {
				m_optionSelecct = 0;
			}
		}
		switch (m_optionSelecct) {
		case 0:
			//カメラ設定
			if (g_pad[0]->IsTrigger(enButtonRight) or g_pad[0]->IsTrigger(enButtonLeft)) {
				m_specialCamera = !m_specialCamera;
			}
			break;
		case 1:
			//BGM設定
			if (g_pad[0]->IsTrigger(enButtonRight)) {
				if (m_bgmVol != 10) {
					m_bgmVol++;
					SoundSource* se = NewGO<SoundSource>(0);
					se->Init(20);
					se->Play(false);
					float finalSE = (m_seVol / 10.0f) * (m_masVol / 10.0f);
					se->SetVolume(finalSE);
				}
			}
			if (g_pad[0]->IsTrigger(enButtonLeft)) {
				if (m_bgmVol != 0) {
					m_bgmVol--;
					SoundSource* se = NewGO<SoundSource>(0);
					se->Init(20);
					se->Play(false);
					float finalSE = (m_seVol / 10.0f) * (m_masVol / 10.0f);
					se->SetVolume(finalSE);
				}
			}
			break;
		case 2:
			//SE設定
			if (g_pad[0]->IsTrigger(enButtonRight)) {
				if (m_seVol != 10) {
					m_seVol++;
					SoundSource* se = NewGO<SoundSource>(0);
					se->Init(20);
					se->Play(false);
					float finalSE = (m_seVol / 10.0f) * (m_masVol / 10.0f);
					se->SetVolume(finalSE);
				}
			}
			if (g_pad[0]->IsTrigger(enButtonLeft)) {
				if (m_seVol != 0) {
					m_seVol--;
					SoundSource* se = NewGO<SoundSource>(0);
					se->Init(20);
					se->Play(false);
					float finalSE = (m_seVol / 10.0f) * (m_masVol / 10.0f);
					se->SetVolume(finalSE);
				}
			}
			break;
		case 3:
			//マスター設定
			if (g_pad[0]->IsTrigger(enButtonRight)) {
				if (m_masVol != 10) {
					m_masVol++;
					SoundSource* se = NewGO<SoundSource>(0);
					se->Init(20);
					se->Play(false);
					float finalSE = (m_seVol / 10.0f) * (m_masVol / 10.0f);
					se->SetVolume(finalSE);
				}
			}
			if (g_pad[0]->IsTrigger(enButtonLeft)) {
				if (m_masVol != 0) {
					m_masVol--;
					SoundSource* se = NewGO<SoundSource>(0);
					se->Init(20);
					se->Play(false);
					float finalSE = (m_seVol / 10.0f) * (m_masVol / 10.0f);
					se->SetVolume(finalSE);
				}
			}
			break;
		case 4:
			if (g_pad[0]->IsTrigger(enButtonA)) {
				m_bgmVol = 10;
				m_seVol = 10;
				m_masVol = 7;
			}
			break;
		case 5:
			if (g_pad[0]->IsTrigger(enButtonA)) {
				m_render.Init("Assets/sprite/title.dds", 1920.0f, 1080.0f);
				SoundSource* se = NewGO<SoundSource>(0);
				se->Init(13);
				se->Play(false);
				float finalSE = (m_seVol / 10.0f) * (m_masVol / 10.0f);
				se->SetVolume(finalSE);
				m_optionSelecct = 0;
				m_optionMode = false;
			}
			break;
		}
	}
	if (m_coolTime == true) {
		m_b.Init("Assets/sprite/a.DDS", 1000.0f, 700.0f);
		if (m_gaugeflug==false)
		{
		m_manualColor += 0.01;
		}
		if(m_gaugeflug ==true) {
			m_manualColor = 0.0;
		}
		m_cool++;
		if (m_cool > 2) {
			m_cool = 3;
		}
		if (g_pad[0]->IsTrigger(enButtonB) and m_cool == 3 and m_j==1)
		{
			m_render.Init("Assets/sprite/title.dds", 1920.0f, 1080.0f);
			m_cool = 0;
			m_coolTime = false;
			m_j = 0;
			m_manualColor = 0.0;
			m_start.Init("Assets/sprite/next.dds", 1000.0f, 700.0f);
			m_sound = NewGO<SoundSource>(0);
			m_sound->Init(13);
			m_sound->Play(false);
			m_sound = NewGO<SoundSource>(0);
			m_sound->Init(11);
			m_sound->Play(true);
		}
	}
	if (m_j == 1 and (g_pad[0]->IsTrigger(enButtonA)) and m_cool > 2) {
		m_render.Init("Assets/sprite/hamachi.dds", 1920.0f, 1080.0f);
		m_gaugeflug = true;
		SoundSource* se = NewGO<SoundSource>(0);
		se->Init(2);
		se->Play(false);
		float finalSE = (m_seVol / 10.0f) * (m_masVol / 10.0f);
		se->SetVolume(finalSE);
		m_j++;
		m_game->Preload();
	}
	if (m_gaugeflug == true) {
		m_gauge.SetPosition({ -600.0f, -8.0f, 0.0f });
		m_scare += 0.339f;
		m_gauge.SetScale({ m_scare,1.0f,0.0f });
		m_gauge.Update();
	}
	if (m_flug == true) {
		if (m_i == 3) {
			if (m_pause == nullptr) {
				m_pause = NewGO<Pause>(1, "Pause");
			}
			NewGO<Water>(0, "Water");
			NewGO<SkyCube>(0, "SkyCube");
			NewGO<GameCamera>(0, "GameCamera");
			if (m_3 == 0) {
				m_font.Init("Assets/sprite/3.dds", 200.0f, 200.0f);
				m_3++;
			}
		}
		if (m_3 == 1) {
			Vector4 FontColor = { 1.0f,1.0f,1.0f, m_fontHaikei };
			m_fontHaikei += 0.02f;
			m_font.SetMulColor(FontColor);
			m_seafont.SetMulColor(FontColor);
		}
		m_count -= 0.015f;
		m_i++;
		m_se++;
	}
	if (m_se == 10) {
		SoundSource* se2 = NewGO<SoundSource>(0);
		se2->Init(8);
		se2->Play(false);
		float finalSE = (m_seVol / 10.0f) * (m_masVol / 10.0f);
		se2->SetVolume(finalSE);
	}
	if (m_count <= 2.0f) {
		if (m_2 == 0) {
			m_font.Init("Assets/sprite/2.dds", 200.0f, 200.0f);
			m_2++;
		}
	}
	if (m_count <= 1.2f) {
		if (m_1 == 0) {
			m_font.Init("Assets/sprite/1.dds", 200.0f, 200.0f);
			m_1++;
		}
	}
	if (m_count <= 0.3f) {
		if (m_GO == 0) {
			m_font.Init("Assets/sprite/GO.dds", 400.0f, 200.0f);
			m_GO++;
		}
		Vector4 color = { 1.0f, 1.0f, 1.0f, m_alpha };
		Vector4 hamachiColor = { 1.0f, 1.0f, 1.0f, m_hamachiAlpha };

		m_alpha -= 0.02f;
		m_hamachiAlpha -= 0.008f;
		m_font.SetMulColor(color);
		m_seafont.SetMulColor(color);
		m_render.SetMulColor(hamachiColor);

	}
	if (m_count <= -0.8f) {
		if (m_newGame == 0) {
			NewGO<Game>(0, "Game");
			m_game = FindGO<Game>("Game");
			m_newGame++;
		}
		if (m_game->m_initialized == true) {
			DeleteGO(this);
		}
	}
	Vector4 manuaColor = { 1.0f,1.0f,1.0f,m_manualColor };
	m_manual.SetMulColor(manuaColor);
	m_b.SetMulColor(manuaColor);
}

void Title::Render(RenderContext& rc) {
	m_render.Draw(rc);
	if (m_optionMode == false) {
		if (m_i > 0) {
			if (m_i < 4) {
				m_gauge.Draw(rc);
			}
			m_font.Draw(rc);
		}
		m_manual.Draw(rc);
		if (m_i < 1) {
			m_start.Draw(rc);
			m_b.Draw(rc);
		}
		if (m_i > 3) {
			m_seafont.Draw(rc);
		}
	}
}