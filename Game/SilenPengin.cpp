#include "stdafx.h"
#include "Player.h"
#include "SilenPengin.h"
#include "Pause.h"

bool SilenPengin::Start() {
	g_soundEngine->ResistWaveFileBank(1, "Assets/Sound/silen.wav");
	m_animationClips[enAnimClip_Chase].Load("Assets/animData/pengin_chase.tka");
	m_animationClips[enAnimClip_Chase].SetLoopFlag(false);
	m_modelRender.Init("Assets/modelData/silenPengin.tkm", m_animationClips, enAnimClip_Num, enModelUpAxisZ);
	m_modelRender.SetScale(15.0f, 15.0f, 15.0f);
	if (m_player == nullptr) {
		m_player = FindGO<Player>("Player");
	}
	m_rot.SetRotationDegY(-90.0f);
	m_modelRender.SetRotation(m_rot);
	m_modelRender.SetPosition(m_pos);
	m_modelRender.Update();
	return true;
}

void SilenPengin::Update() {
	m_pause = FindGO<Pause>("Pause");
	if (m_pause && m_pause->IsPaused()) {
		return;
	}

	Vector3 diff = m_player->m_position - m_pos;
	if (m_player->m_swim == false) {
		m_coolTime -= 0.1f;
	}
	if (m_coolTime > 0.0f) {
		m_pos = { m_player->m_position.x,0.0f,m_player->m_position.z };
		m_pos.x += 3000.0f;
	}
	if (m_coolTime <= 35.0f and m_player->m_swim == false) {
		m_se = NewGO<SoundSource>(0);
		for (; m_silen < 1; m_silen++) {
			m_se->Init(1);
			float finalSE = (m_pause->m_sevolume / 10.0f) * (m_pause->m_master / 10.0f);
			m_se->SetVolume(finalSE);
			m_se->Play(false);

		}
		if (m_player->m_swim == true) {
			if (m_se != nullptr);
		}
	}
	if (m_coolTime <= 0.0f) {
		if (m_player->m_swim == true) {
			m_pos.x += 50.0f;
		}
		else if (diff.Length() >= 600.0f) {
			m_pos.x -= 50.0f;
		}
		else {
			m_pos.x -= 1.0f;
		}
	}
	if (m_coolTime <= -1000.0f) {
		m_coolTime = 100.0f;
		m_silen = 0;
	}
	m_modelRender.SetPosition(m_pos);
	m_modelRender.Update();
}

void SilenPengin::Render(RenderContext& rc) {
	if (m_coolTime <= 0.0f and m_coolTime >= -100.0f) {
		m_modelRender.Draw(rc);
	}
}
