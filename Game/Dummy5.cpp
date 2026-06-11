#include "stdafx.h"
#include "Dummy5.h"
#include "NinjaPengin.h"
#include "Player.h"
#include "Pause.h"

bool  Dummy5::Start() {
	m_animationClips[enAnimClip_Walk].Load("Assets/animData/pengin_walk.tka");
	m_animationClips[enAnimClip_Walk].SetLoopFlag(true);
	m_animationClips[enAnimClip_Chase].Load("Assets/animData/pengin_chase.tka");
	m_animationClips[enAnimClip_Chase].SetLoopFlag(false);
	m_modelRender.Init("Assets/modelData/pengin.tkm", m_animationClips, enAnimClip_Num, enModelUpAxisZ);
	m_effectEmitter = NewGO <EffectEmitter>(0);
	m_effectEmitter->Init(0);
	m_effectEmitter->SetScale({ 20.0f,20.0f,20.0f });
	m_effectEmitter->Play();
	m_pos = { 0.0f,0.0f,9999000.0f };
	m_modelRender.SetScale(15.0f, 15.0f, 15.0f);
	m_modelRender.SetRotation(m_rot);
	m_modelRender.SetPosition(m_pos);
	m_characterController.Init(75.0f, 75.0f, m_pos);
	m_ninjaPengin = FindGO<NinjaPengin>("NinjaPengin");
	m_modelRender.Update();
	return true;
}

void  Dummy5::Update() {
	m_modelRender.PlayAnimation(enAnimClip_Chase);
	auto pause = FindGO<Pause>("Pause");
	if (pause and pause->IsPaused()) {
		return;
	}
	Vector3 moveSpeed;
	if (m_player == nullptr) {
		m_player = FindGO<Player>("Player");
		return;
	}
	Vector3 diff = m_player->m_position - m_pos;
	if (diff.Length() <= 2000.0f and diff.Length() >= 600.0f and m_player->m_swim == false) {
		float distToPlayer = diff.Length();
		Vector3 toPlayerDir = diff;
		toPlayerDir.Normalize();
		if (m_player->m_superJump == false) {
			moveSpeed += toPlayerDir * 15.0f;
			float angleY = atan2f(toPlayerDir.x, toPlayerDir.z);
			// ラジアンを度数に変換し、回転行列を作成
			m_rot.SetRotationY(angleY);
		}
		else {
			moveSpeed.z -= 15.0f;
		}
	}
	else if (diff.Length() <= 600.0f and m_player->m_swim == false) {
		if (m_effect != 15) {
			m_effect++;
		}
		if (m_effect >= 15) {
			m_effectEmitter->Stop();
		}
		float distToPlayer = diff.Length();
		Vector3 toPlayerDir = diff;
		toPlayerDir.Normalize();
		if (m_player->m_superJump == false) {
			moveSpeed += toPlayerDir * 0.1f;
			float angleY = atan2f(toPlayerDir.x, toPlayerDir.z);
			// ラジアンを度数に変換し、回転行列を作成
			m_rot.SetRotationY(angleY);
		}
		else {
			Vector3 diff = m_player->m_position - m_pos;
			Vector3 toPlayerDir = diff;
			toPlayerDir.Normalize();
			// プレイヤー方向を向く角度
			float angleY = atan2f(toPlayerDir.x, toPlayerDir.z);
			m_rot.SetRotationY(angleY);
			// ここで「前方向」を作る
			Vector3 forward;
			forward.x = sinf(angleY);
			forward.y = 0.0f;
			forward.z = cosf(angleY);
			moveSpeed += forward * 8.0f;
		}
	}
	else if (m_player->m_swim == true) {
		Vector3 diff = m_pos - m_player->m_position;
		float distToPlayer = diff.Length();
		Vector3 toPlayerDir = diff;
		toPlayerDir.Normalize();
		moveSpeed += toPlayerDir * 5.0f;
	}
	else {
		moveSpeed.z -= 1.0f;
	}
	if (m_ninjaPengin && m_ninjaPengin->m_change == true) {
		if (m_i < 1) {
			m_oldPos = m_pos;
			m_characterController.SetPosition(m_ninjaPengin->m_oldPos);
			m_i++;
		}
	}
	else {
		m_rot.SetRotationDegY(180.0f);
	}
	moveSpeed.y = 0.0f;
	m_pos = m_characterController.Execute(moveSpeed, 5.0f);
	m_modelRender.SetRotation(m_rot);
	m_modelRender.SetPosition(m_pos);
	m_effectEmitter->SetPosition(m_pos);
	m_modelRender.Update();
}

void  Dummy5::Render(RenderContext& rc) {
	m_modelRender.Draw(rc);
}
