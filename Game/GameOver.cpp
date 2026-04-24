#include "stdafx.h"
#include "GameOver.h"
#include "Title.h"
#include "Pause.h"

bool GameOver::Start() {
	m_render.Init("Assets/sprite/gameover.dds", 1920.0f, 1080.0f);
	auto pause = FindGO<Pause>("Pause");
	m_bgm = NewGO<SoundSource>(0);
	m_bgm->Init(10);
	m_bgm->Play(false);
	float finalSE = (pause->m_volume / 10.0f) * (pause->m_master / 10.0f);
	m_bgm->SetVolume(finalSE);
	return true;
}

void GameOver::Update() {
	if (m_change == false) {
		m_color += 0.01f;
	}
	if (m_color > 1.0f) {
		m_color = 1.0f;
	}
	m_render.SetMulColor({ 1.0f, 1.0f, 1.0f, m_color });
	if (g_pad[0]->IsTrigger(enButtonA)) {
		DeleteGO(m_bgm);
		m_change = true;
		if (m_i == 0) {
			NewGO<Title>(0, "Title");
		}
		m_i++;
	}
	if (m_change == true) {
		m_color -= 0.01;
	}
	if (m_color < 0.0f) {
		DeleteGO(this);
	}
	m_render.Update();
}

void GameOver::Render(RenderContext& rc) {
	m_render.Draw(rc);
}