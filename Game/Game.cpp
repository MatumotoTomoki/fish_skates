#include "stdafx.h"
#include "Game.h"
#include "GameClear.h"
#include "GameCamera.h"
#include "GameOver.h"
#include "Player.h"
#include "Water.h"
#include "Dummy.h"
#include "Dummy3.h"
#include "Dummy5.h"
#include "Distance.h"
#include "UI.h"
#include "Pengin.h"
#include "NinjaPengin.h"
#include "SilenPengin.h"
#include "Pause.h"
#include "Title.h"
#include "Arrow.h"

void Game::Preload() {
	g_soundEngine->ResistWaveFileBank(0, "Assets/Sound/fish.wav");
	g_soundEngine->ResistWaveFileBank(1, "Assets/Sound/silen.wav");
	g_soundEngine->ResistWaveFileBank(3, "Assets/sound/pause.wav");
	g_soundEngine->ResistWaveFileBank(4, "Assets/sound/select.wav");
	g_soundEngine->ResistWaveFileBank(5, "Assets/sound/ok.wav");
	g_soundEngine->ResistWaveFileBank(6, "Assets/sound/cancel.wav");
	g_soundEngine->ResistWaveFileBank(7, "Assets/sound/hole.wav");
	g_soundEngine->ResistWaveFileBank(9, "Assets/sound/GameClear.wav");
	g_soundEngine->ResistWaveFileBank(10, "Assets/sound/Gameover.wav");
	g_soundEngine->ResistWaveFileBank(14, "Assets/sound/jump.wav");
	g_soundEngine->ResistWaveFileBank(15, "Assets/sound/superjump.wav");
	g_soundEngine->ResistWaveFileBank(16, "Assets/sound/chase.wav");
	g_soundEngine->ResistWaveFileBank(17, "Assets/sound/Menu.wav");
	g_soundEngine->ResistWaveFileBank(18, "Assets/sound/Hial.wav");
	g_soundEngine->ResistWaveFileBank(19, "Assets/sound/damage.wav");
	EffectEngine::GetInstance()->ResistEffect(0, u"Assets/effect/magic_sphere.efk");
	EffectEngine::GetInstance()->ResistEffect(1, u"Assets/effect/Wave.efk");
	EffectEngine::GetInstance()->ResistEffect(2, u"Assets/effect/jump.efk");
	Title* title = FindGO<Title>("Title");
	title->m_flug = true;
}

bool Game::Start() {
	QueryPerformanceFrequency((LARGE_INTEGER*)&m_freq);
	QueryPerformanceCounter((LARGE_INTEGER*)&m_prevTime);
	m_stageLevelRnder.Init("Assets/modelData/Stage2.tkl", [&](LevelObjectData& odData) {
		m_skyCube = FindGO<SkyCube>("SkyCube");
		m_water = FindGO<Water>("Water");
		m_pause = FindGO<Pause>("Pause");
		m_gameCamera = FindGO<GameCamera>("GameCamera");
		if (odData.EqualObjectName(L"fish") == true)
		{
			m_modelRender.Init("Assets/modelData/fish/Fish.tkm");
			m_modelRender.SetTRS(
				odData.position,
				odData.rotation,
				odData.scale);
			return true;
		}
		if (odData.EqualObjectName(L"Stage") == true) {
			m_stageRender.Init("Assets/modelData/tairiku4.tkm");
			m_stageRender.SetTRS(
				odData.position,
				odData.rotation,
				odData.scale);
			m_stageRender.SetPosition(0.0f, 0.0f, 0.0f);
			m_stageRender.SetScale(100.0f, 100.0f, 100.0f);
			m_stageRender.Update();
			m_physicsStaticObject.CreateFromModel(
				m_stageRender.GetModel(),
				m_stageRender.GetModel().GetWorldMatrix()
			);
			return true;
		}
		});
	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
	return true;
}

void Game::Update() {
	long long now;
	QueryPerformanceCounter((LARGE_INTEGER*)&now);

	m_deltaTime = (float)(now - m_prevTime) / (float)m_freq;
	m_prevTime = now;

	if (m_deltaTime > 0.0f) {
		m_fps = 1.0f / m_deltaTime;
	}

	if (!m_initialized) {
		switch (m_loadStep) {
		case 0:
			m_player = NewGO<Player>(0, "Player");
			m_pengin = NewGO<Pengin>(0, "Pengin");
			m_ninjaPengin = NewGO<NinjaPengin>(0, "NinjaPengin");
			m_silenPengin = NewGO<SilenPengin>(0, "SilenPengin");
			m_dummy = NewGO<Dummy>(0, "Dummy");
			m_dummy3 = NewGO<Dummy3>(0, "Dummy3");
			m_dummy5 = NewGO<Dummy5>(0, "Dummy5");
			break;
		case 1:
			m_ui = NewGO<UI>(0, "ui");
			break;
		case 2:
			m_distance = NewGO<Distance>(0, "Distance");
			m_arrow = NewGO<Arrow>(0, "Arrow");
			break;
		case 3:
			m_gameBGM = NewGO<SoundSource>(0);
			m_gameBGM->Init(0);
			m_gameBGM->Play(true);
			if (m_pause) {
				float finalSE = (m_pause->m_volume / 10.0f) * (m_pause->m_master / 10.0f);
				m_gameBGM->SetVolume(finalSE);
			}
			m_initialized = true;
			break;
		}
		m_loadStep++;
	}
	if (g_pad[0]->IsTrigger(enButtonStart) and m_initialized == true) {
		m_menuSE = NewGO<SoundSource>(0);
		m_menuSE->Init(3);
		m_menuSE->Play(false);
		float finalSE = (m_pause->m_sevolume / 10.0f) * (m_pause->m_master / 10.0f);
		m_menuSE->SetVolume(finalSE);
		m_stop = !m_stop;
	}
	if (m_stop == true) {
		if (m_pause->m_mode == 3) {
			if (g_pad[0]->IsTrigger(enButtonA)) {
				m_menuSE = NewGO<SoundSource>(0);
				m_menuSE->Init(3);
				m_menuSE->Play(false);
				float finalSE = (m_pause->m_sevolume / 10.0f) * (m_pause->m_master / 10.0f);
				m_menuSE->SetVolume(finalSE);
				m_stop = !m_stop;
			}
		}
		if (m_pause->m_mode != 3) {
			if (g_pad[0]->IsTrigger(enButtonA) and m_pause->m_soundTest == false) {
				m_pause->m_soundTest = true;
				m_menuSE = NewGO<SoundSource>(0);
				m_menuSE->Init(5);
				m_menuSE->Play(false);
				float finalSE = (m_pause->m_sevolume / 10.0f) * (m_pause->m_master / 10.0f);
				m_menuSE->SetVolume(finalSE);

			}
		}
		if (m_pause->m_soundTest == true) {
			if (g_pad[0]->IsTrigger(enButtonB)) {
				m_pause->m_soundTest = false;
				m_menuSE = NewGO<SoundSource>(0);
				m_menuSE->Init(6);
				m_menuSE->Play(false);
				float finalSE = (m_pause->m_sevolume / 10.0f) * (m_pause->m_master / 10.0f);
				m_menuSE->SetVolume(finalSE);
			}
		}
		if (m_pause->m_soundMode == 3) {
			if (g_pad[0]->IsTrigger(enButtonA)) {
				m_menuSE = NewGO<SoundSource>(0);
				m_menuSE->Init(5);
				m_menuSE->Play(false);
				float finalSE = (m_pause->m_sevolume / 10.0f) * (m_pause->m_master / 10.0f);
				m_menuSE->SetVolume(finalSE);
			}
		}
		if (m_pause->m_soundMode == 4) {
			if (g_pad[0]->IsTrigger(enButtonA)) {
				m_pause->m_soundTest = false;
				m_menuSE = NewGO<SoundSource>(0);
				m_menuSE->Init(6);
				m_menuSE->Play(false);
				float finalSE = (m_pause->m_sevolume / 10.0f) * (m_pause->m_master / 10.0f);
				m_menuSE->SetVolume(finalSE);
			}
		}
		if (g_pad[0]->IsTrigger(enButtonUp) or g_pad[0]->IsTrigger(enButtonDown)) {
			m_selectSE = NewGO<SoundSource>(0);
			m_selectSE->Init(4);
			m_selectSE->Play(false);
			float finalSE = (m_pause->m_sevolume / 10.0f) * (m_pause->m_master / 10.0f);
			m_selectSE->SetVolume(finalSE);
		}
		if (g_pad[0]->IsTrigger(enButtonLeft) and m_pause->m_soundTest == true and m_pause->m_soundMode <= 2 and m_pause->m_select != 0) {
			m_selectSE = NewGO<SoundSource>(0);
			m_selectSE->Init(4);
			m_selectSE->Play(false);
			float finalSE = (m_pause->m_sevolume / 10.0f) * (m_pause->m_master / 10.0f);
			m_selectSE->SetVolume(finalSE);
		}
		if (g_pad[0]->IsTrigger(enButtonRight) and m_pause->m_select != 10 and m_pause->m_soundTest == true and m_pause->m_soundMode <= 2) {
			m_selectSE = NewGO<SoundSource>(0);
			m_selectSE->Init(4);
			m_selectSE->Play(false);
			float finalSE = (m_pause->m_sevolume / 10.0f) * (m_pause->m_master / 10.0f);
			m_selectSE->SetVolume(finalSE);
		}
	}
	if (m_player->m_o2 >= -0.1f) {
		DeleteGO(m_pengin);
		DeleteGO(m_ninjaPengin);
		DeleteGO(m_silenPengin);
		DeleteGO(m_gameCamera);
		DeleteGO(m_player);
		DeleteGO(m_gameBGM);
		DeleteGO(m_chaseBGM);
		DeleteGO(m_ui);
		DeleteGO(m_water);
		DeleteGO(m_dummy);
		DeleteGO(m_dummy3);
		DeleteGO(m_dummy5);
		DeleteGO(m_skyCube);
		DeleteGO(m_distance);
		DeleteGO(m_arrow);
		NewGO<GameOver>(0, "GameOver");
		DeleteGO(this);
	}
	if (m_player->m_hp >= -0.1f) {
		DeleteGO(m_pengin);
		DeleteGO(m_ninjaPengin);
		DeleteGO(m_silenPengin);
		DeleteGO(m_gameCamera);
		DeleteGO(m_player);
		DeleteGO(m_gameBGM);
		DeleteGO(m_chaseBGM);
		DeleteGO(m_ui);
		DeleteGO(m_water);
		DeleteGO(m_dummy);
		DeleteGO(m_dummy3);
		DeleteGO(m_dummy5);
		DeleteGO(m_skyCube);
		DeleteGO(m_distance);
		DeleteGO(m_arrow);
		NewGO<GameOver>(0, "GameOver");
		DeleteGO(this);
	}
	else if (m_player->m_position.z >= 7500.0f) {
		DeleteGO(m_pengin);
		DeleteGO(m_ninjaPengin);
		DeleteGO(m_silenPengin);
		DeleteGO(m_gameCamera);
		DeleteGO(m_player);
		DeleteGO(m_gameBGM);
		DeleteGO(m_chaseBGM);
		DeleteGO(m_ui);
		DeleteGO(m_water);
		DeleteGO(m_dummy);
		DeleteGO(m_dummy3);
		DeleteGO(m_dummy5);
		DeleteGO(m_skyCube);
		DeleteGO(m_distance);
		DeleteGO(m_arrow);
		NewGO<GameClear>(0, "GameClear");
		DeleteGO(this);
	}
	else if (m_pause->m_return == true) {
		DeleteGO(m_pengin);
		DeleteGO(m_ninjaPengin);
		DeleteGO(m_silenPengin);
		DeleteGO(m_gameCamera);
		DeleteGO(m_player);
		DeleteGO(m_gameBGM);
		DeleteGO(m_chaseBGM);
		DeleteGO(m_ui);
		DeleteGO(m_water);
		DeleteGO(m_dummy);
		DeleteGO(m_dummy3);
		DeleteGO(m_dummy5);
		DeleteGO(m_skyCube);
		DeleteGO(m_distance);
		DeleteGO(m_arrow);
		m_pause->m_return = false;
		DeleteGO(this);
	}
	if (m_player->m_chase == true and m_pause->m_isPause == false) {
		if (m_chaseBGM == nullptr) {
			if (m_pause->m_mode != 1) {
				DeleteGO(m_gameBGM);
				m_gameBGM = nullptr;
				m_chaseBGM = NewGO<SoundSource>(0);
				m_chaseBGM->Init(16);
				m_chaseBGM->Play(true);
				float vol = (m_pause->m_volume / 10.0f) * (m_pause->m_master / 10.0f);
				m_chaseBGM->SetVolume(vol);
				m_bgmJustChanged = true;   // ← ロマン発動
			}
		}
	}
	if (m_player->m_chase == false) {
		if (m_chaseBGM != nullptr) {
			DeleteGO(m_chaseBGM);
			m_chaseBGM = nullptr;
			m_gameBGM = NewGO<SoundSource>(0);
			m_gameBGM->Init(0);
			m_gameBGM->Play(true);
			float vol = (m_pause->m_volume / 10.0f) * (m_pause->m_master / 10.0f);
			m_gameBGM->SetVolume(vol);
		}
	}
	float targetRatio = 1.0f;
	if (m_player->m_hp > -0.34f or m_player->m_o2 > -0.34f) {
		targetRatio = 1.1f;
	}
	if (!m_bgmJustChanged) {
		if (m_gameBGM and m_gameBGM->IsPlaying())
			m_gameBGM->SetFrequencyRatio(targetRatio);

		if (m_chaseBGM and m_chaseBGM->IsPlaying())
			m_chaseBGM->SetFrequencyRatio(targetRatio);
	}
	if (m_pause->m_isPause == true and m_isPause == 0){
		DeleteGO(m_gameBGM);
		m_gameBGM = nullptr;
		DeleteGO(m_chaseBGM);
		m_chaseBGM = nullptr;
		m_pauseBGM = NewGO<SoundSource>(0);
		m_pauseBGM->Init(17);
		m_pauseBGM->Play(true);
		m_isPause++;
		float vol = (m_pause->m_volume / 10.0f) * (m_pause->m_master / 10.0f);
		m_pauseBGM->SetVolume(vol);
	}
	if (m_pause->m_isPause == false and m_isPause == 1){
		DeleteGO(m_pauseBGM);
		m_pauseBGM = nullptr;
		float vol = (m_pause->m_volume / 10.0f) * (m_pause->m_master / 10.0f);
		if (m_chaseBGM == nullptr) {
			if (m_pause->m_mode != 1) {
				m_gameBGM = NewGO<SoundSource>(0);
				m_gameBGM->Init(0);
				m_gameBGM->Play(true);
				if (m_gameBGM) {
					m_gameBGM->SetVolume(vol);
				}
			}
		}
		else {
			// チェイス中なら chaseBGM の音量をいじる
			if (m_chaseBGM) {
				m_chaseBGM->SetVolume(vol);
			}
		}
		m_isPause--;
	}
	m_bgmJustChanged = false;  // ← ロマン終了
	m_stageRender.Update();
	m_modelRender.Update();
	//リリースでのFPS確認用
	wchar_t fpsText[64];
	swprintf(fpsText, 64, L"FPS: %.1f", m_fps);
	m_fpsFont.SetText(fpsText);
	m_fpsFont.SetPosition({ -900.0f,420.0f,0.0f });
}

void Game::Render(RenderContext& rc) {
	m_stageRender.Draw(rc);
	//m_fpsFont.Draw(rc);		//リリースでのFPS確認用
}