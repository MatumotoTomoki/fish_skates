#include "stdafx.h"
#include "UI.h"
#include "Player.h"
#include "Pause.h"
#include "GameCamera.h"

bool UI::Start() {
	m_spriteRender.Init("Assets/sprite/distance.dds", 650.0f, 630.0f);
	m_spriteRender.SetPosition({ -740.0f,480.0f,0.0f });
	m_spriteRender2.Init("Assets/sprite/hpGaugeFlame.dds", 600.0f, 390.0f);
	m_spriteRender2.SetPosition({ 780.0f,480.0f,0.0f });
	m_spriteRender3.Init("Assets/sprite/rsaes-eh35n.dds", 340.0f, 25.0f);
	m_spriteRender3.SetPosition({ 780.0f,485.0f,0.0f });
	m_spriteRender4.Init("Assets/sprite/o2GaugeFlame.dds", 570.0f, 390.0f);
	m_spriteRender4.SetPosition({ 780.0f,375.0f,0.0f });
	m_spriteRender5.Init("Assets/sprite/rsaes-eh35n.dds", 340.0f, 25.0f);
	m_spriteRender5.SetPosition({ 780.0f,385.0f,0.0f });
	m_spriteRender3.SetMulColor({ 0.0f,1.0f,0.0f,1.0f });
	m_spriteRender5.SetMulColor({ 0.0f,1.0f,1.0f,1.0f });
	m_startRender.Init("Assets/sprite/StartJP.dds", 900.0f, 600.0f);
	if (m_player == nullptr) {
		m_player = FindGO<Player>("Player");
	}
	return true;
}

void UI::Update() {
	auto pause = FindGO<Pause>("Pause");
	if (pause and pause->IsPaused()) {
		return;
	}
	if (m_player->m_hp > -0.74f) {
		m_spriteRender3.SetMulColor({ 0.0f,1.0f,0.0f,1.0f });
	}
	if (m_player->m_hp > -0.64f) {
		m_spriteRender3.SetMulColor({ 1.0f,1.0f,0.0f,1.0f });
		if (m_hpUI == 0) {
			m_hpUI++;
		}
	}
	if (m_player->m_hp > -0.44f) {
		m_spriteRender3.SetMulColor({ 1.0f,0.0f,0.0f,1.0f });
		if (m_hpUI == 1) {
			m_hpUI++;
		}
	}
	if (m_player->m_hp > -0.34f and m_hpUI <= 6) {
		m_spriteRender3.SetMulColor({ 1.0f,0.0f,0.0f,1.0f });
		m_hpUI++;
	}
	if (m_player->m_hp > -0.34f and m_hpUI == 7) {
		m_spriteRender3.SetMulColor({ 0.0f,0.0f,0.0f,1.0f });
		m_hpUI -= 5;
	}
	if (m_player->m_o2 > -0.74f) {
		m_spriteRender5.SetMulColor({ 0.0f,1.0f,1.0f,1.0f });
	}
	if (m_player->m_o2 > -0.64f) {
		m_spriteRender5.SetMulColor({ 1.0f,1.0f,0.0f,1.0f });
		if (m_o2UI == 0) {
			m_o2UI++;
		}
	}
	if (m_player->m_o2 > -0.44f) {
		m_spriteRender5.SetMulColor({ 1.0f,0.0f,0.0f,1.0f });
		if (m_o2UI == 1) {
			m_o2UI++;
		}
	}
	if (m_player->m_o2 > -0.34f and m_o2UI <= 6) {
		m_spriteRender5.SetMulColor({ 1.0f,0.0f,0.0f,1.0f });
		m_o2UI++;
	}
	if (m_player->m_o2 > -0.34f and m_o2UI == 7) {
		m_spriteRender5.SetMulColor({ 0.0f,0.0f,0.0f,1.0f });
		m_o2UI -= 5;
	}
	auto camera = FindGO<GameCamera>("GameCamera");
	if (camera->m_flug == true) {
		if (m_alpha > 0.0f) {
			m_alpha -= 0.02f;
			m_startRender.SetMulColor({ 1.0f, 1.0f, 1.0f, m_alpha });
		}
		if (m_alpha <= 1.0f and m_se == false) {
			SoundSource* se = NewGO<SoundSource>(0);
			se->Init(21);
			se->Play(false);
			float finalSE = (pause->m_sevolume / 10.0f) * (pause->m_master / 10.0f);
			se->SetVolume(finalSE);
			m_se = true;
		}
	}
	m_spriteRender5.SetPivot({ 1.0,0.53f });
	m_spriteRender5.SetScale({ m_player->m_o2,1.0f,0.0f });
	m_spriteRender5.SetPosition({ 600.0f,385.0f,0.0f });
	m_spriteRender3.SetPivot({ 1.0,0.53f });
	m_spriteRender3.SetScale({ m_player->m_hp,1.0f,0.0f });
	m_spriteRender3.SetPosition({ 600.0f,485.0f,0.0f });
	m_spriteRender.Update();
	m_spriteRender2.Update();
	m_spriteRender3.Update();
	m_spriteRender4.Update();
	m_spriteRender5.Update();
	m_startRender.Update();
}

void UI::Render(RenderContext& rc) {
	auto camera = FindGO<GameCamera>("GameCamera");
	if (camera->m_flug == true) {
		m_spriteRender.Draw(rc);
		m_spriteRender3.Draw(rc);
		m_spriteRender2.Draw(rc);
		m_spriteRender5.Draw(rc);
		m_spriteRender4.Draw(rc);
		m_startRender.Draw(rc);
	}
}
