#include "stdafx.h"
#include "Title.h"
#include "Game.h"
#include "Pause.h"
#include "Water.h"

bool Title::Start() {
	m_render.Init("Assets/sprite/title.dds", 1920.0f, 1080.0f);
	g_soundEngine->ResistWaveFileBank(2, "Assets/Sound/start.wav");
	g_soundEngine->ResistWaveFileBank(8, "Assets/Sound/countdown.wav");
	m_pause = FindGO<Pause>("Pause");
	return true;
}

void Title::Update() {
	if (g_pad[0]->IsTrigger(enButtonA)and m_j == 0) {
		m_render.Init("Assets/sprite/backGround.dds", 1920.0f, 1080.0f);
		m_font.SetText(L"ロード中");
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
	if (m_flug == true) {
		if (m_i == 3) {
			m_pause = NewGO<Pause>(0, "Pause");
			NewGO<Water>(0);
			m_seafont.SetText(L"海を目指せ！");
			m_seafont.SetPosition(-100.0f, -200.0f, 0.0f);
			m_font.SetText(L"3");
		}
		m_count -= 0.015f;
		m_i++;
		m_se++;
	}
	if (m_se == 10) {
		SoundSource* se2 = NewGO<SoundSource>(0);
		se2->Init(8);
		se2->Play(false);
		se2->SetVolume(2.5f);
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
	m_render.Draw(rc);
	m_font.Draw(rc);
	m_seafont.Draw(rc);

}