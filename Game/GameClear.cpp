#include "stdafx.h"
#include "GameClear.h"
#include "Title.h"
#include "Pause.h"

bool GameClear::Start() {
	m_spriteRender.Init("Assets/sprite/GameClear.dds", 1920.0f, 1080.0f);
	auto pause = FindGO<Pause>("Pause");
	m_bgm = NewGO<SoundSource>(0);
	m_bgm->Init(9);
	m_bgm->Play(false);
	float finalSE = (pause->m_volume / 10.0f) * (pause->m_master / 10.0f);
	m_bgm->SetVolume(finalSE);
	return true;
}

void GameClear::Update() {
	if (m_change == false) {
		m_color += 0.01f;
	}
	if (m_color > 1.0f) {
		m_color = 1.0f;
	}
	m_spriteRender.SetMulColor({ 1.0f, 1.0f, 1.0f, m_color });
	if (g_pad[0]->IsTrigger(enButtonA)) {
		DeleteGO(m_bgm);
		m_change = true;
		if (m_i == 0) {
			NewGO<Title>(0, "Title");
		}
		m_i++;
	}
	if (m_change == true) {
		m_color -= 0.01f;
	}
	if (m_color < 0.0f) {
		DeleteGO(this);
	}
	m_spriteRender.Update();
}

void GameClear::Render(RenderContext& rc) {
	m_spriteRender.Draw(rc);
}

