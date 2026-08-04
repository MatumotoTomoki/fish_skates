#include "stdafx.h"
#include "UI.h"
#include "Player.h"
#include "Pause.h"
#include "GameCamera.h"
#include "SilenPengin.h"

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
	m_warningRender.Init("Assets/sprite/p.dds", 340.0f, 256.0f);
	m_warningRender.SetPosition({ 0.0f,400.0f,0.0f });
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
	if (m_player->m_start == true) {
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
	if (m_player->m_start == true) {
		m_warningFlag = false;
		if (m_player->m_diff.Length() <= 1800.0f or m_player->m_diff2.Length() <= 1800.0f or m_player->m_diff3.Length() <= 1800.0f or m_player->m_diff4.Length() <= 1800.0f or m_player->m_diff5.Length() <= 1800.0f) {
			m_warningFlag = true;
		}
	}
	Vector3 pos = m_player->m_position;
	wchar_t buf[128];
	swprintf(buf, 128, L"Pos: X = %.1f Y = %.1f Z = %.1f", pos.x, pos.y, pos.z);
	// 共通の速度で値を変化させる
	float speed = 0.01f;
	//取った下駄のカウント
	wchar_t text[64];
	swprintf_s(text, L"スピードダウンカウント : %d", m_player->m_getaCount);
	//スピードアップの残り時間
	float remain = 3.0f - m_player->m_supermovetime;

	wchar_t speedText[64];
	swprintf_s(speedText, L"スピードアップ %.1f", remain);

	//酸素ストップの残り時間
	float o2stop = 3.0f - m_player->m_o2stoptime;

	wchar_t o2Text[64];
	swprintf_s(o2Text, L"酸素ストップ%.1f", o2stop);

	// 0.0〜1.0の間を往復させるためのシンプルロジック
	auto updateColorValue = [&](float& val, bool& dir, float spd) {
		if (dir) {
			val += spd;
			if (val >= 1.0f) { val = 1.0f; dir = false; }
		}
		else {
			val -= spd;
			if (val <= 0.0f) { val = 0.0f; dir = true; }
		}
		};
	updateColorValue(m_posColor, m_color, speed);
	updateColorValue(m_posColor1, m_color1, speed);
	updateColorValue(m_posColor2, m_color2, speed);
	m_font.SetColor(m_posColor, m_posColor1, m_posColor2, 1.0f);
	m_font.SetText(buf);
	m_getafont.SetText(text);
	m_speedfont.SetText(speedText);
	m_o2font.SetText(o2Text);
	m_getafont.SetPosition({ -800.0f,0.0f,0.0f });
	m_speedfont.SetPosition({ -800.0f,-50.0f,0.0f });
	m_o2font.SetPosition({ -800.0f,-100.0f,0.0f });
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
	m_warningRender.Update();
}

void UI::Render(RenderContext& rc) {
	m_font.Draw(rc);
	if (m_player->m_start == true) {
		m_spriteRender.Draw(rc);
		m_spriteRender3.Draw(rc);
		m_spriteRender2.Draw(rc);
		m_spriteRender5.Draw(rc);
		m_spriteRender4.Draw(rc);
		m_startRender.Draw(rc);
		if (m_warningFlag == true and m_player->m_swim == false) {
			m_warningRender.Draw(rc);
		}
		if (m_player->m_getaCount > 0) {
			m_getafont.Draw(rc);
		}
		if (m_player->m_superMoveGet == true) {
			m_speedfont.Draw(rc);
		}
		if (m_player->m_o2StopGet == true) {
			m_o2font.Draw(rc);
		}
	}
	
}
