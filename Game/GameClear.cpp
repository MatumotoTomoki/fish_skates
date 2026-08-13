#include "stdafx.h"
#include "GameClear.h"
#include "Title.h"
#include "Pause.h"

bool GameClear::Start() {
	auto pause = FindGO<Pause>("Pause");
	if (pause->m_clearCount == 0) {
		m_spriteRender.Init("Assets/sprite/GameClear.dds", 1920.0f, 1080.0f);
	}
	else if (pause->m_clearCount == 1) {
		m_spriteRender.Init("Assets/sprite/stageClear.dds", 1920.0f, 1080.0f);
	}
	m_nextRender.Init("Assets/sprite/next.dds", 1000.0f, 700.0f);
	m_nextRender.SetPosition({ 0.0f,-300.0f,0.0f });
	m_bgm = NewGO<SoundSource>(0);
	m_bgm->Init(9);
	m_bgm->Play(false);
	float finalSE = (pause->m_volume / 10.0f) * (pause->m_master / 10.0f);
	m_bgm->SetVolume(finalSE);
	return true;
}

void GameClear::Update() {
	if (m_flug == true) {
		m_nextColor -= 0.01f;
	}
	if (m_nextColor >= 1.0f) {
		m_flug = true;
	}
	if (m_flug == false) {
		m_nextColor += 0.01f;
	}
	if (m_nextColor <= 0.0f) {
		m_flug = false;
	}
	m_nextRender.SetMulColor({ 1.0f,1.0f,1.0f,m_nextColor });
	if (g_pad[0]->IsTrigger(enButtonA)) {
		if (m_change == false) {
			auto pause = FindGO<Pause>("Pause");
			SoundSource* se = NewGO<SoundSource>(0);
			se->Init(5);
			float finalSE = (pause->m_sevolume / 10.0f) * (pause->m_master / 10.0f);
			se->SetVolume(finalSE);
			se->Play(false);
		}
		DeleteGO(m_bgm);
		m_change = true;
		if (m_i == 0) {
			NewGO<Title>(0, "Title");
		}
		m_i++;
	}
	if (m_change == false) {
		m_color += 0.01f;
	}
	if (m_color > 1.0f) {
		m_color = 1.0f;
	}
	if (m_change == true) {
		m_color = 0.0f;
	}
	if (m_color == 0.0f) {
		DeleteGO(this);
	}
	m_spriteRender.SetMulColor({ 1.0f, 1.0f, 1.0f, m_color });
	m_spriteRender.Update();
	m_nextRender.Update();
}

void GameClear::Render(RenderContext& rc) {
	m_spriteRender.Draw(rc);
	m_nextRender.Draw(rc);
}

