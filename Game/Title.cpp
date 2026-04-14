#include "stdafx.h"
#include "Title.h"
#include "Game.h"
#include "Pause.h"
#include "Water.h"
#include "GameCamera.h"

bool Title::Start() {
	m_render.Init("Assets/sprite/title.dds", 1920.0f, 1080.0f);
	g_soundEngine->ResistWaveFileBank(2, "Assets/Sound/start.wav");
	g_soundEngine->ResistWaveFileBank(8, "Assets/Sound/countdown.wav");
	m_font.Init("Assets/sprite/Gaugeflame.dds", 1600.0f, 200.0f);
	m_gauge.Init("Assets/sprite/Gauge.dds", 1600.0f, 200.0f);
	m_seafont.Init("Assets/sprite/sea.dds", 600.0f, 400.0f);
	m_seafont.SetPosition({ 10.0f, -200.0f, 0.0f });
	m_start.Init("Assets/sprite/start.dds", 1000.0f, 700.0f);
	m_start.SetPosition({ 0.0f,-300.0f,0.0f });
	m_font.SetPosition({ 0.0f, 0.0f, 0.0f });
	m_gauge.SetPosition({ -600.0f, -7.0f, 0.0f });
	m_gauge.SetPivot({ 0.13f,0.5f });
	m_gauge.SetScale({ -1600.0f,200.0f,0.0f });
	m_pause = FindGO<Pause>("Pause");
	m_gauge.Update();
	m_seafont.Update();
	m_start.Update();
	return true;
}

void Title::Update() {
	if (g_pad[0]->IsTrigger(enButtonA) and m_j == 0) {
		m_render.Init("Assets/sprite/hamachi.dds", 1920.0f, 1080.0f);
		m_gaugeflug = true;
		m_j++;
		SoundSource* se = NewGO<SoundSource>(0);
		se->Init(2);
		se->Play(false);
		if (m_pause) {
			float finalSE = (m_pause->m_sevolume / 10.0f) * (m_pause->m_master / 10.0f);
			se->SetVolume(finalSE);
		}
		else {
			se->SetVolume(2.5f);
		}
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
				m_pause = NewGO<Pause>(0, "Pause");
			}
			NewGO<Water>(0);
			NewGO<SkyCube>(0, "SkyCube");
			NewGO<GameCamera>(0, "GameCamera");
			if (m_3 == 0) {
				m_font.Init("Assets/sprite/3.dds", 200.0f, 200.0f);
				m_3++;
			}
		}
		m_count -= 0.015f;
		m_i++;
		m_se++;
	}
	if (m_se == 10) {
		SoundSource* se2 = NewGO<SoundSource>(0);
		se2->Init(8);
		se2->Play(false);
		if (m_pause) {
			float finalSE = (m_pause->m_sevolume / 10.0f) * (m_pause->m_master / 10.0f);
			se2->SetVolume(finalSE);
		}
		else {
			se2->SetVolume(2.5f);
		}
	}
	if (m_count <= 2.0f) {
		if (m_2 == 0) {
			m_font.Init("Assets/sprite/2.dds", 200.0f, 200.0f);
			m_2++;
		}
	}
	if (m_count <= 1.0f) {
		if (m_1 == 0) {
			m_font.Init("Assets/sprite/1.dds", 200.0f, 200.0f);
			m_1++;
		}
	}
	if (m_count <= 0.0f) {
		if (m_GO == 0) {
			m_font.Init("Assets/sprite/GO.dds", 400.0f, 200.0f);
			m_GO++;
		}
	}
	if (m_count <= -1.0f) {
		if (m_newGame == 0) {
			NewGO<Game>(0, "Game");
			m_game = FindGO<Game>("Game");
			m_newGame++;
		}
		if (m_game->m_initialized == true) {
			DeleteGO(this);
		}
	}
}

void Title::Render(RenderContext& rc) {
	m_render.Draw(rc);
	if (m_i < 1) {
		m_start.Draw(rc);
	}
	if (m_i > 0) {
		if (m_i < 4) {
			m_gauge.Draw(rc);
		}
		m_font.Draw(rc);
	}
	if (m_i > 3) {
		m_seafont.Draw(rc);
	}
}