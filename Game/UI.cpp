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
	m_countRender.Init("Assets/sprite/3.dds", 250.0f, 250.0f);
	if (m_player == nullptr) {
		m_player = FindGO<Player>("Player");
	}
	m_warningRender.Init("Assets/sprite/p.dds", 340.0f, 256.0f);
	m_warningRender.SetPosition({ 0.0f,400.0f,0.0f });
	m_o2stopRender.Init("Assets/sprite/O2stop.dds", 150.0f, 100.0f);
	m_o2stopRender.SetPosition({ -700.0f,-100.0f,0.0f });
	m_o2CountRender3.Init("Assets/sprite/3.dds", 75.0f, 75.0f);
	m_o2CountRender3.SetPosition({ -500.0f,-100.0f,0.0f });
	m_o2CountRender2.Init("Assets/sprite/2.dds", 75.0f, 75.0f);
	m_o2CountRender2.SetPosition({ -500.0f,-100.0f,0.0f });
	m_o2CountRender1.Init("Assets/sprite/1.dds", 75.0f, 75.0f);
	m_o2CountRender1.SetPosition({ -500.0f,-100.0f,0.0f });
	m_speedUpRender.Init("Assets/sprite/Speedup.dds", 150.0f, 100.0f);
	m_speedUpRender.SetPosition({ -700.0f,-50.0f,0.0f });
	m_speedCountRender.Init("Assets/sprite/3.dds", 75.0f, 75.0f);
	m_speedCountRender.SetPosition({ -500.0f,-50.0f,0.0f });
	m_speedDownRender.Init("Assets/sprite/Speeddowncount.dds", 150.0f, 100.0f);
	m_speedDownRender.SetPosition({ -700.0f,0.0f,0.0f });
	m_downCountRender.Init("Assets/sprite/5.dds", 75.0f, 75.0f);
	m_downCountRender.SetPosition({ -500.0f,0.0f,0.0f });
	return true;
}

void UI::Update() {
	auto pause = FindGO<Pause>("Pause");
	if (pause and pause->IsPaused()) {
		return;
	}
	auto camera = FindGO<GameCamera>("GameCamera");
	if (m_player->m_characterController.IsOnGround() == true) {
		SoundSource* se;
		if (m_secount == 0 and m_countDown <= 3.0f) {
			se = NewGO<SoundSource>(0);
			se->Init(8);
			se->Play(false);
			float finalSE = (pause->m_sevolume / 10.0f) * (pause->m_master / 10.0f);
			se->SetVolume(finalSE);
			m_secount++;
		}
		m_countDown -= 0.021f;
		if (m_countDown <= 1.6f and m_number == 2) {
			m_countRender.Init("Assets/sprite/2.dds", 250.0f, 250.0f);
			m_number--;
		}
		if (m_countDown <= 0.4f and m_number == 1) {
			m_countRender.Init("Assets/sprite/1.dds", 250.0f, 250.0f);
			m_number--;
		}
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
	if (m_player->m_o2StopGet == true) {
		m_o2stopRender.Update();
		if (m_player->m_o2stoptime >= 0.0f and m_player->m_o2stoptime < 1.0f) {
			m_o2CountRender3.Update();
		}
		if (m_player->m_o2stoptime >= 1.0f and m_player->m_o2stoptime < 2.0f) {
			m_o2CountRender2.Update();
		}
		if (m_player->m_o2stoptime >= 2.0f) {
			m_o2CountRender1.Update();
		}
		
	}
	if (m_player->m_superMoveGet == true) {
		m_speedUpRender.Update();
		if (m_player->m_supermovetime >= 0.0f and m_player->m_supermovetime < 1.0f) {
			m_speedCountRender.Init("Assets/sprite/3.dds", 75.0f, 75.0f);
		}
		else if (m_player->m_supermovetime >= 1.0f and m_player->m_supermovetime < 2.0f) {
			m_speedCountRender.Init("Assets/sprite/2.dds", 75.0f, 75.0f);
		}
		else {
			m_speedCountRender.Init("Assets/sprite/1.dds", 75.0f, 75.0f);
		}
		m_speedCountRender.Update();
	}
	if (m_player->m_getaCount > 0) {
		m_speedDownRender.Update();
		if (m_player->m_getaCount == 1) {
			m_downCountRender.Init("Assets/sprite/1.dds", 75.0f, 75.0f);
		}
		else if (m_player->m_getaCount == 2) {
			m_downCountRender.Init("Assets/sprite/2.dds", 75.0f, 75.0f);
		}
		else if (m_player->m_getaCount == 3) {
			m_downCountRender.Init("Assets/sprite/3.dds", 75.0f, 75.0f);
		}
		else if (m_player->m_getaCount == 4) {
			m_downCountRender.Init("Assets/sprite/4.dds", 75.0f, 75.0f);
		}
		else {
			m_downCountRender.Init("Assets/sprite/5.dds", 75.0f, 75.0f);
		}
		m_downCountRender.Update();
	}
}

void UI::Render(RenderContext& rc) {
	m_font.Draw(rc);
	if (m_countDown <= 3.0f and m_player->m_start == false) {
		m_countRender.Draw(rc);
	}
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
			m_speedDownRender.Draw(rc);
			if (m_player->m_getaCount == 1) {
				m_downCountRender.Draw(rc);
			}
			else if (m_player->m_getaCount == 2) {
				m_downCountRender.Draw(rc);
			}
			else if (m_player->m_getaCount == 3) {
				m_downCountRender.Draw(rc);
			}
			else if (m_player->m_getaCount == 4) {
				m_downCountRender.Draw(rc);
			}
			else {
				m_downCountRender.Draw(rc);
			}
		}
		if (m_player->m_superMoveGet == true) {
			m_speedUpRender.Draw(rc);
			if (m_player->m_supermovetime >= 0.0f and m_player->m_supermovetime < 1.0f) {
				m_o2CountRender3.Draw(rc);
			}
			else if (m_player->m_supermovetime >= 1.0f and m_player->m_supermovetime < 2.0f) {
				m_o2CountRender2.Draw(rc);
			}
			else {
				m_o2CountRender1.Draw(rc);
			}
		}
		if (m_player->m_o2StopGet == true) {
			m_o2stopRender.Draw(rc);
			if (m_player->m_o2stoptime >= 0.0f and m_player->m_o2stoptime < 1.0f) {
				m_speedCountRender.Draw(rc);
			}
			if (m_player->m_o2stoptime >= 1.0f and m_player->m_o2stoptime < 2.0f) {
				m_speedCountRender.Draw(rc);
			}
			if (m_player->m_o2stoptime >= 2.0f) {
				m_speedCountRender.Draw(rc);
			}
		}
	}
}
