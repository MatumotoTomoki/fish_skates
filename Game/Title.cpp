#include "stdafx.h"
#include "Title.h"
#include "Game.h"
#include "Pause.h"

bool Title::Start() {
	m_render.Init("Assets/sprite/title.dds", 1920.0f, 1080.0f);
	g_soundEngine->ResistWaveFileBank(2, "Assets/Sound/start.wav");
	m_pause = FindGO<Pause>("Pause");
	return true;
}

void Title::Update() {
	if (g_pad[0]->IsTrigger(enButtonA)) {
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
		m_flug = true;
		m_font.SetText(L"3");
		m_game->Preload();
	}
	if (m_flug == true) {
		m_count -= 0.015f;
	}
	if (m_count <= 2.0f) {
		m_font.SetText(L"2");
	}
	if (m_count <= 1.0f) {
		m_font.SetText(L"1");
	}
	if (m_count <= 0.0f) {
		m_font.SetText(L"GO!");
	}
	if (m_count <= -1.0f) {
		NewGO<Game>(0, "Game");
		DeleteGO(this);
	}
}

void Title::Render(RenderContext& rc) {
	if (m_flug == false) {
		m_render.Draw(rc);
	}
	m_font.Draw(rc);
}