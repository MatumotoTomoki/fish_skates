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
	m_gauge.SetPosition({ -600.0f, -7.0f, 0.0f });
	m_gauge.SetPivot({ 0.13f,0.5f });
	m_gauge.SetScale({ -1600.0f,200.0f,0.0f });
	m_bgmOption.Init("Assets/sprite/soundMove.dds", 1920.0f, 1080.0f);
	m_bgmGauge.Init("Assets/sprite/bar10.dds", 1000.0f, 700.0f);
	m_seOption.Init("Assets/sprite/seMove.dds", 1920.0f, 1080.0f);
	m_seGauge.Init("Assets/sprite/bar10.dds", 1000.0f, 700.0f);
	m_masOption.Init("Assets/sprite/masterMove.dds", 1920.0f, 1080.0f);
	m_masGauge.Init("Assets/sprite/bar7.dds", 1000.0f, 700.0f);
	m_arrow.Init("Assets/sprite/allow.dds", 300.0f, 200.0f);
	m_cameraOption.Init("Assets/sprite/cameraOption.dds", 750.0f, 450.0f);
	m_cameraCamera.Init("Assets/sprite/cameraCamera.dds", 770.0f, 470.0f);
	m_charaCamera.Init("Assets/sprite/charaCamera.dds", 850.0f, 550.0f);
	m_optionButton.Init("Assets/sprite/option.dds", 900.0f, 600.0f);
	m_defaultOption.Init("Assets/sprite/defalt.dds", 700.0f, 500.0f);
	m_returnOption.Init("Assets/sprite/returnTitle.dds", 1890.0f, 1050.0f);
	m_start.SetPosition({ -300.0f,-300.0f,0.0f });
	m_font.SetPosition({ 0.0f, 0.0f, 0.0f });
	m_cameraOption.SetPosition({ -330.0f,340.0f,0.0f });
	m_cameraCamera.SetPosition({ 30.0f,340.0f,0.0f });
	m_charaCamera.SetPosition({ 500.0f,340.0f,0.0f });
	m_optionButton.SetPosition({ 300.0f,-280.0f,0.0f });
	m_defaultOption.SetPosition({ -300.0f,-300.0f,0.0f });
	m_returnOption.SetPosition({ -170.0f,-300.0f,0.0f });
	m_bgmOption.SetPosition({ -100.0f,0.0f,0.0f });
	m_bgmGauge.SetPosition({ 110.0f,180.0f,0.0f });
	m_seOption.SetPosition({ -100.0f,0.0f,0.0f });
	m_seGauge.SetPosition({ 110.0f,20.0f,0.0f });
	m_masOption.SetPosition({ -100.0f,0.0f,0.0f });
	m_masGauge.SetPosition({ 110.0f,-140.0f,0.0f });
	m_b.Update();
	m_gauge.Update();
	m_seafont.Update();
	m_start.Update();
	m_manual.Update();
	m_bgmOption.Update();
	m_bgmGauge.Update();
	m_seOption.Update();
	m_seGauge.Update();
	m_masOption.Update();
	m_masGauge.Update();
	m_defaultOption.Update();
	m_arrow.Update();
	m_returnOption.Update();
	m_cameraOption.Update();
	m_cameraCamera.Update();
	m_charaCamera.Update();
	return true;
}

void Title::Update() {
	Vector4 titleColor = { 1.0f,1.0f,1.0f,m_titleColor };
	Vector4 stopColor = { 1.0f,1.0f,m_stopColor, m_stopColor};
	m_titleColor += 0.01f;
	Vector4 startColor;
	if (m_coolTime == false) {
		startColor = { 1.0f, 1.0f, m_startColor, m_startColor };
	}
	else {
		startColor = { 1.0f, 1.0f, 1.0f, m_startColor };
	}
	if (m_optionState == false) {
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
		stopColor = { 1.0f,1.0f,1.0f, 1.0f };
	}
	else {
		if (m_stopColor >= 1.0f) {
			m_stopAlpha = false;
		}
		if (m_stopColor <= 0.0f) {
			m_stopAlpha = true;
		}
		if (m_stopAlpha == false) {
			m_stopColor -= 0.01f;
		}
		if (m_stopAlpha == true) {
			m_stopColor += 0.01f;
		}
		m_startAlpha == true;
		startColor = { 1.0f, 1.0f, 1.0f, 1.0f };
	}
	m_start.SetMulColor(startColor);
	m_optionButton.SetMulColor(stopColor);
	if (g_pad[0]->IsTrigger(enButtonRight) or g_pad[0]->IsTrigger(enButtonLeft)) {
		if (m_optionMode == false and m_coolTime == false) {
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
	if (m_specialCamera == false) {
		m_cameraCamera.SetScale({ 1.07f,1.07f,1.0f });
		m_charaCamera.SetScale({ 1.0f,1.0f,1.0f });
	}
	else {
		m_cameraCamera.SetScale({ 1.0f,1.0f,1.0f });
		m_charaCamera.SetScale({ 1.07f,1.07f,1.0f });
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
			m_arrow.SetPosition({ -580.0f,350.0f,0.0f });
			if (g_pad[0]->IsTrigger(enButtonRight) and m_specialCamera == false) {
				m_specialCamera = true;
				SoundSource* se = NewGO<SoundSource>(0);
				se->Init(20);
				se->Play(false);
				float finalSE = (m_seVol / 10.0f) * (m_masVol / 10.0f);
				se->SetVolume(finalSE);
			}
			if (g_pad[0]->IsTrigger(enButtonLeft) and m_specialCamera == true) {
				m_specialCamera = false;
				SoundSource* se = NewGO<SoundSource>(0);
				se->Init(20);
				se->Play(false);
				float finalSE = (m_seVol / 10.0f) * (m_masVol / 10.0f);
				se->SetVolume(finalSE);
			}
			m_bgmOption.SetScale({ 1.0f,1.0f,1.0f });
			m_seOption.SetScale({ 1.0f,1.0f,1.0f });
			m_masOption.SetScale({ 1.0f,1.0f,1.0f });
			m_cameraOption.SetScale({ 1.05f,1.05f,1.0f });
			m_defaultOption.SetScale({ 1.0f,1.0f,1.0f });
			m_returnOption.SetScale({ 1.0f,1.0f,1.0f });
			break;
		case 1:
			//BGM設定
			m_arrow.SetPosition({ -580.0f,190.0f,0.0f });
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
			m_bgmOption.SetScale({ 1.05f,1.05f,1.0f });
			m_seOption.SetScale({ 1.0f,1.0f,1.0f });
			m_masOption.SetScale({ 1.0f,1.0f,1.0f });
			m_cameraOption.SetScale({ 1.0f,1.0f,1.0f });
			m_defaultOption.SetScale({ 1.0f,1.0f,1.0f });
			m_returnOption.SetScale({ 1.0f,1.0f,1.0f });
			break;
		case 2:
			//SE設定
			m_arrow.SetPosition({ -580.0f,25.0f,0.0f });
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
			m_bgmOption.SetScale({ 1.0f,1.0f,1.0f });
			m_seOption.SetScale({ 1.05f,1.05f,1.0f });
			m_masOption.SetScale({ 1.0f,1.0f,1.0f });
			m_cameraOption.SetScale({ 1.0f,1.0f,1.0f });
			m_defaultOption.SetScale({ 1.0f,1.0f,1.0f });
			m_returnOption.SetScale({ 1.0f,1.0f,1.0f });
			break;
		case 3:
			//マスター設定
			m_arrow.SetPosition({ -580.0f,-130.0f,0.0f });
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
			m_bgmOption.SetScale({ 1.0f,1.0f,1.0f });
			m_seOption.SetScale({ 1.0f,1.0f,1.0f });
			m_masOption.SetScale({ 1.05f,1.05f,1.0f });
			m_cameraOption.SetScale({ 1.0f,1.0f,1.0f });
			m_defaultOption.SetScale({ 1.0f,1.0f,1.0f });
			m_returnOption.SetScale({ 1.0f,1.0f,1.0f });
			break;
		case 4:
			//デフォルトに戻す
			m_arrow.SetPosition({ -580.0f,-290.0f,0.0f });
			if (g_pad[0]->IsTrigger(enButtonA)) {
				m_bgmVol = 10;
				m_seVol = 10;
				m_masVol = 7;
				m_specialCamera = false;
				SoundSource* se = NewGO<SoundSource>(0);
				se->Init(12);
				se->Play(false);
				float finalSE = (m_seVol / 10.0f) * (m_masVol / 10.0f);
				se->SetVolume(finalSE);
			}
			m_bgmOption.SetScale({ 1.0f,1.0f,1.0f });
			m_seOption.SetScale({ 1.0f,1.0f,1.0f });
			m_masOption.SetScale({ 1.0f,1.0f,1.0f });
			m_cameraOption.SetScale({ 1.0f,1.0f,1.0f });
			m_defaultOption.SetScale({ 1.05f,1.05f,1.05f });
			m_returnOption.SetScale({ 1.0f,1.0f,1.0f });
			break;
		case 5:
			//タイトルに戻る
			m_arrow.SetPosition({ -580.0f,-440.0f,0.0f });
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
			m_bgmOption.SetScale({ 1.0f,1.0f,1.0f });
			m_seOption.SetScale({ 1.0f,1.0f,1.0f });
			m_masOption.SetScale({ 1.0f,1.0f,1.0f });
			m_cameraOption.SetScale({ 1.0f,1.0f,1.0f });
			m_defaultOption.SetScale({ 1.0f,1.0f,1.0f });
			m_returnOption.SetScale({ 1.05f,1.05f,1.0f });
			break;
		}
		switch (m_bgmVol) {
		case 1:
			m_bgmGauge.Init("Assets/sprite/bar1.dds", 500.0f, 150.0f);
			break;
		case 2:
			m_bgmGauge.Init("Assets/sprite/bar2.dds", 500.0f, 150.0f);
			break;
		case 3:
			m_bgmGauge.Init("Assets/sprite/bar3.dds", 500.0f, 150.0f);
			break;
		case 4:
			m_bgmGauge.Init("Assets/sprite/bar4.dds", 500.0f, 150.0f);
			break;
		case 5:
			m_bgmGauge.Init("Assets/sprite/bar5.dds", 500.0f, 150.0f);
			break;
		case 6:
			m_bgmGauge.Init("Assets/sprite/bar6.dds", 500.0f, 150.0f);
			break;
		case 7:
			m_bgmGauge.Init("Assets/sprite/bar7.dds", 500.0f, 150.0f);
			break;
		case 8:
			m_bgmGauge.Init("Assets/sprite/bar8.dds", 500.0f, 150.0f);
			break;
		case 9:
			m_bgmGauge.Init("Assets/sprite/bar9.dds", 500.0f, 150.0f);
			break;
		case 10:
			m_bgmGauge.Init("Assets/sprite/bar10.dds", 500.0f, 150.0f);
			break;
		}
		switch (m_seVol) {
		case 1:
			m_seGauge.Init("Assets/sprite/bar1.dds", 500.0f, 150.0f);
			break;
		case 2:
			m_seGauge.Init("Assets/sprite/bar2.dds", 500.0f, 150.0f);
			break;
		case 3:
			m_seGauge.Init("Assets/sprite/bar3.dds", 500.0f, 150.0f);
			break;
		case 4:
			m_seGauge.Init("Assets/sprite/bar4.dds", 500.0f, 150.0f);
			break;
		case 5:
			m_seGauge.Init("Assets/sprite/bar5.dds", 500.0f, 150.0f);
			break;
		case 6:
			m_seGauge.Init("Assets/sprite/bar6.dds", 500.0f, 150.0f);
			break;
		case 7:
			m_seGauge.Init("Assets/sprite/bar7.dds", 500.0f, 150.0f);
			break;
		case 8:
			m_seGauge.Init("Assets/sprite/bar8.dds", 500.0f, 150.0f);
			break;
		case 9:
			m_seGauge.Init("Assets/sprite/bar9.dds", 500.0f, 150.0f);
			break;
		case 10:
			m_seGauge.Init("Assets/sprite/bar10.dds", 500.0f, 150.0f);
			break;
		}
		switch (m_masVol) {
		case 1:
			m_masGauge.Init("Assets/sprite/bar1.dds", 500.0f, 150.0f);
			break;
		case 2:
			m_masGauge.Init("Assets/sprite/bar2.dds", 500.0f, 150.0f);
			break;
		case 3:
			m_masGauge.Init("Assets/sprite/bar3.dds", 500.0f, 150.0f);
			break;
		case 4:
			m_masGauge.Init("Assets/sprite/bar4.dds", 500.0f, 150.0f);
			break;
		case 5:
			m_masGauge.Init("Assets/sprite/bar5.dds", 500.0f, 150.0f);
			break;
		case 6:
			m_masGauge.Init("Assets/sprite/bar6.dds", 500.0f, 150.0f);
			break;
		case 7:
			m_masGauge.Init("Assets/sprite/bar7.dds", 500.0f, 150.0f);
			break;
		case 8:
			m_masGauge.Init("Assets/sprite/bar8.dds", 500.0f, 150.0f);
			break;
		case 9:
			m_masGauge.Init("Assets/sprite/bar9.dds", 500.0f, 150.0f);
			break;
		case 10:
			m_masGauge.Init("Assets/sprite/bar10.dds", 500.0f, 150.0f);
			break;
		}
		m_bgmGauge.Update();
		m_seGauge.Update();
		m_masGauge.Update();
	}
	if (m_coolTime == true) {
		m_start.SetPosition({ 0.0f,-300.0f,0.0f });
		m_start.Update();
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
		if (g_pad[0]->IsTrigger(enButtonB) and m_cool == 3 and m_j==1){
			m_start.SetPosition({ -300.0f,-300.0f,0.0f });
			m_start.Update();
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
			auto skyCube = NewGO<SkyCube>(0, "SkyCube");
			skyCube->SetType((EnSkyCubeType)m_skyCubeType);
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
	m_arrow.Update();
	m_returnOption.Update();
	m_cameraOption.Update();
	m_cameraCamera.Update();
	m_charaCamera.Update();
	m_bgmOption.Update();
	m_seOption.Update();
	m_masOption.Update();
	m_defaultOption.Update();
	m_returnOption.Update();
	m_optionButton.Update();
}

void Title::Render(RenderContext& rc) {
	m_render.Draw(rc);
	if (m_coolTime == false) {
		if (m_optionMode == false) {
			m_optionButton.Draw(rc);
		}
	}
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
	else {
		m_bgmOption.Draw(rc);
		m_cameraOption.Draw(rc);
		m_cameraCamera.Draw(rc);
		m_charaCamera.Draw(rc);
		m_defaultOption.Draw(rc);
		m_returnOption.Draw(rc);
		if (m_bgmVol != 0) {
			m_bgmGauge.Draw(rc);
		}
		m_seOption.Draw(rc);
		if (m_seVol != 0) {
			m_seGauge.Draw(rc);
		}
		m_masOption.Draw(rc);
		if (m_masVol != 0) {
			m_masGauge.Draw(rc);
		}
		m_arrow.Draw(rc);
	}
}