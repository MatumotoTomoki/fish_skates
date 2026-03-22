#include "stdafx.h"
#include "Game.h"
#include "GameClear.h"
#include "GameCamera.h"
#include "GameOver.h"
#include "Player.h"
#include"sound/SoundEngine.h"
#include "Water.h"
#include "Dummy.h"
#include "Dummy3.h"
#include "Dummy5.h"
#include "UI.h"
#include "Pengin.h"
#include "NinjaPengin.h"
#include "SilenPengin.h"
#include "Pause.h"
#include "Title.h"

// ★追加（BGMとSEのスイッチ）
bool m_isBgmOn = true;
bool m_isSeOn = true;

bool Game::Start()
{
	m_stageLevelRnder.Init("Assets/modelData/Stage2.tkl", [&](LevelObjectData& odData)
		{
			if (odData.EqualObjectName(L"fish") == true)
			{
				m_modelRender.Init("Assets/modelData/fish/Fish.tkm");
				m_modelRender.SetTRS(
					odData.position,
					odData.rotation,
					odData.scale);
				m_player = NewGO<Player>(0, "Player");
				m_gameCamera = NewGO<GameCamera>(0, "GameCamera");
				m_ui = NewGO<UI>(0, "ui");
				m_pengin = NewGO<Pengin>(0, "Pengin");
				m_ninjaPengin = NewGO<NinjaPengin>(0, "NinjaPengin");
				m_silenPengin = NewGO<SilenPengin>(0, "SilenPengin");
				m_pause = NewGO<Pause>(0, "Pause");
				// SE読み込み
				g_soundEngine->ResistWaveFileBank(0, "Assets/Sound/fish.wav");
				g_soundEngine->ResistWaveFileBank(3, "Assets/sound/pause.wav");
				g_soundEngine->ResistWaveFileBank(4, "Assets/sound/select.wav");
				g_soundEngine->ResistWaveFileBank(5, "Assets/sound/ok.wav");
				g_soundEngine->ResistWaveFileBank(6, "Assets/sound/cancel.wav");

				// BGM
				m_gameBGM = NewGO<SoundSource>(0);
				m_gameBGM->Init(0);
				m_gameBGM->Play(true);

				m_skyCube = NewGO<SkyCube>(0);
				Water* water = NewGO<Water>(0);
				m_dummy = NewGO<Dummy>(0, "Dummy");
				m_dummy3 = NewGO<Dummy3>(0, "Dummy3");
				m_dummy5 = NewGO<Dummy5>(0, "Dummy5");

				return true;
			}

			if (odData.EqualObjectName(L"Stage") == true)
			{
				m_stageRender.Init("Assets/modelData/tairiku3.tkm");
				m_stageRender.SetTRS(
					odData.position,
					odData.rotation,
					odData.scale);
				m_stageRender.SetPosition(0.0f, -475.0f, 0.0f);
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

void Game::Update()
{
	if (g_pad[0]->IsTrigger(enButtonStart)) {
		m_menuSE = NewGO<SoundSource>(0);
		m_menuSE->Init(3);
		m_menuSE->Play(false);
		m_menuSE->SetVolume(m_pause->m_sevolume);
		m_stop = !m_stop;
	}
	if (m_stop == true) {
		if (m_pause->m_mode == 3) {
			if (g_pad[0]->IsTrigger(enButtonA)) {
				m_menuSE = NewGO<SoundSource>(0);
				m_menuSE->Init(3);
				m_menuSE->Play(false);
				m_menuSE->SetVolume(m_pause->m_sevolume);
				m_stop = !m_stop;
			}
		}
		if (m_pause->m_mode != 3) {
			if (g_pad[0]->IsTrigger(enButtonA) and m_pause->m_soundTest == false) {
				m_menuSE = NewGO<SoundSource>(0);
				m_menuSE->Init(5);
				m_menuSE->Play(false);
				m_menuSE->SetVolume(m_pause->m_sevolume);

			}
		}
		if (g_pad[0]->IsTrigger(enButtonB) and m_pause->m_soundTest == true) {
			m_menuSE = NewGO<SoundSource>(0);
			m_menuSE->Init(6);
			m_menuSE->Play(false);
			m_menuSE->SetVolume(m_pause->m_sevolume);
		}
		if (g_pad[0]->IsTrigger(enButtonUp) or g_pad[0]->IsTrigger(enButtonDown)) {
			m_selectSE = NewGO<SoundSource>(0);
			m_selectSE->Init(4);
			m_selectSE->Play(false);
			m_selectSE->SetVolume(m_pause->m_sevolume);
		}
		if (g_pad[0]->IsTrigger(enButtonLeft) and m_pause->m_soundTest == true) {
			m_selectSE = NewGO<SoundSource>(0);
			m_selectSE->Init(4);
			m_selectSE->Play(false);
			m_selectSE->SetVolume(m_pause->m_sevolume);
		}
		if (g_pad[0]->IsTrigger(enButtonRight) and m_pause->m_sevolume != 10 and m_pause->m_soundTest == true) {
			m_selectSE = NewGO<SoundSource>(0);
			m_selectSE->Init(4);
			m_selectSE->Play(false);
			m_selectSE->SetVolume(m_pause->m_sevolume);
		}
	}

	if (m_player->m_o2 >= -0.1f) {
		DeleteGO(m_pengin);
		DeleteGO(m_ninjaPengin);
		DeleteGO(m_silenPengin);
		DeleteGO(m_gameCamera);
		DeleteGO(m_player);
		DeleteGO(m_gameBGM);
		DeleteGO(m_ui);
		DeleteGO(m_water);
		DeleteGO(m_dummy);
		DeleteGO(m_dummy3);
		DeleteGO(m_dummy5);
		DeleteGO(m_pause);
		m_gameOver = NewGO<GameOver>(0, "GameOver");
		DeleteGO(this);
	}

	if (m_player->m_hp >= -0.1f) {
		DeleteGO(m_pengin);
		DeleteGO(m_ninjaPengin);
		DeleteGO(m_silenPengin);
		DeleteGO(m_gameCamera);
		DeleteGO(m_player);
		DeleteGO(m_gameBGM);
		DeleteGO(m_ui);
		DeleteGO(m_water);
		DeleteGO(m_dummy);
		DeleteGO(m_dummy3);
		DeleteGO(m_dummy5);
		DeleteGO(m_pause);
		m_gameOver = NewGO<GameOver>(0, "GameOver");
		DeleteGO(this);
	}

	if (m_player->m_position.z >= 7500.0f) {
		DeleteGO(m_pengin);
		DeleteGO(m_ninjaPengin);
		DeleteGO(m_silenPengin);
		DeleteGO(m_gameCamera);
		DeleteGO(m_player);
		DeleteGO(m_gameBGM);
		DeleteGO(m_ui);
		DeleteGO(m_water);
		DeleteGO(m_dummy);
		DeleteGO(m_dummy3);
		DeleteGO(m_dummy5);
		DeleteGO(m_pause);
		NewGO<GameClear>(0, "GameClear");
		DeleteGO(this);
	}
	auto title = FindGO<Title>("Title");
	if (title) {
		DeleteGO(m_pengin);
		DeleteGO(m_ninjaPengin);
		DeleteGO(m_silenPengin);
		DeleteGO(m_gameCamera);
		DeleteGO(m_player);
		DeleteGO(m_gameBGM);
		DeleteGO(m_ui);
		DeleteGO(m_water);
		DeleteGO(m_dummy);
		DeleteGO(m_dummy3);
		DeleteGO(m_dummy5);
		DeleteGO(m_pause);
		DeleteGO(this);
	}

	m_stageRender.Update();
	m_modelRender.Update();
}

void Game::Render(RenderContext& rc)
{
	m_stageRender.Draw(rc);
	m_modelRender.Draw(rc);
}