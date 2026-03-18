#include "stdafx.h"
#include "NinjaPengin.h"
#include "Player.h"
#include "Dummy.h"
#include "Pause.h"

bool NinjaPengin::Start() {
	m_animationClips[enAnimClip_Walk].Load("Assets/animData/pengin_walk.tka");
	m_animationClips[enAnimClip_Walk].SetLoopFlag(true);
	m_animationClips[enAnimClip_Chase].Load("Assets/animData/pengin_chase.tka");
	m_animationClips[enAnimClip_Chase].SetLoopFlag(false);
	m_modelRender.Init("Assets/modelData/ninja_pengin.tkm", m_animationClips, enAnimClip_Num, enModelUpAxisZ);
	m_pos = { 0.0f,0.0f,3000.0f };
	m_dummy = FindGO<Dummy>("Dummy");
	m_modelRender.SetScale(15.0f, 15.0f, 15.0f);
	m_modelRender.SetRotation(m_rot);
	m_modelRender.SetPosition(m_pos);
	m_characterController.Init(75.0f, 75.0f, m_pos);
	m_modelRender.Update();
	m_cb.Init(sizeof(SCustomCb), nullptr);
	m_opacity = 0.0f;
	return true;
}

void NinjaPengin::Update() {
	auto pause = FindGO<Pause>("Pause");
	if (pause && pause->IsPaused()) {
		return;
	}

	Vector3 moveSpeed;
	m_modelRender.PlayAnimation(enAnimClip_Chase);
	if (m_player == nullptr) {
		m_player = FindGO<Player>("Player");
		return;
	}

	Vector3 diff = m_player->m_position - m_pos;
	if (diff.Length() <= 2000.0f and diff.Length() >= 600.0f and  m_player->m_swim == false) {
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
		m_stealth = false;
	}
	else if (diff.Length() <= 600.0f  and m_player->m_swim == false) {
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
			moveSpeed.z -= 15.0f;
		}
		m_pos = m_characterController.Execute(moveSpeed, 1.0f);
		m_stealth = false;
	}
	else if (m_player->m_swim == true) {
		Vector3 diff = m_pos - m_player->m_position;
		float distToPlayer = diff.Length();

		Vector3 toPlayerDir = diff;
		toPlayerDir.Normalize();

		moveSpeed += toPlayerDir * 5.0f;

		float angleY = atan2f(toPlayerDir.x, toPlayerDir.z);
		m_rot.SetRotationY(-angleY);

		m_stealth = true;
	}
	else {
		m_rot.SetRotationDegY(180.0f);
		m_stealth = true;
	}

	/*if (m_dummy->m_change == true) {
		for (; m_i < 1; m_i++) {
			m_characterController.SetPosition(m_dummy->m_oldPos);
		}
	}*/

	moveSpeed.y = 0.0f;
	moveSpeed.z -= 1.0f;
	m_pos = m_characterController.Execute(moveSpeed, 1.0f);
	m_modelRender.SetRotation(m_rot);
	m_modelRender.SetPosition(m_pos);
	
	// だんだん現れる（例：1秒強で出現）
	if (!m_stealth) {
		m_opacity += 0.005f;
	}
	else {
		m_opacity -= 0.01f;
	}
	m_opacity = fmaxf(0.0f, fminf(1.0f, m_opacity));

	m_modelRender.Update();
}

void NinjaPengin::Render(RenderContext& rc) {
	if (m_opacity > 0.0f) {
		SCustomCb cbData;
		cbData.opacity = m_opacity; // ここで Update で計算した値を渡す！
		cbData.isDither = 1.0f;     // ペンギンは常に網目対象

		m_cb.CopyToVRAM(&cbData);
		rc.SetConstantBuffer(1, m_cb);

		m_modelRender.Draw(rc);

		// 背景を守るためのお掃除（フラグを0にする）
		SCustomCb resetData;
		resetData.opacity = 1.0f;
		resetData.isDither = 0.0f; // 他の描画では網目機能をOFFにする
		m_cb.CopyToVRAM(&resetData);
		rc.SetConstantBuffer(1, m_cb);
	}
}
