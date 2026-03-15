#include "stdafx.h"
#include "Dummy.h"
#include "NinjaPengin.h"
#include "Player.h"

bool  Dummy::Start() {
	m_animationClips[enAnimClip_Walk].Load("Assets/animData/pengin_walk.tka");
	m_animationClips[enAnimClip_Walk].SetLoopFlag(true);
	m_animationClips[enAnimClip_Chase].Load("Assets/animData/pengin_chase.tka");
	m_animationClips[enAnimClip_Chase].SetLoopFlag(false);
	m_modelRender.Init("Assets/modelData/pengin_dummy.tkm", m_animationClips, enAnimClip_Num, enModelUpAxisZ);
	m_pos = { 0.0f,0.0f,3000.0f };
	m_modelRender.SetScale(15.0f, 15.0f, 15.0f);
	m_modelRender.SetRotation(m_rot);
	m_modelRender.SetPosition(m_pos);
	m_characterController.Init(75.0f, 75.0f, m_pos);
	m_ninjaPengin = FindGO<NinjaPengin>("NinjaPengin");
	m_modelRender.Update();
	return true;
}

void  Dummy::Update() {
	Vector3 moveSpeed;
	if (m_player == nullptr) {
		m_player = FindGO<Player>("Player");
		return;
	}

	Vector3 diff = m_player->m_position - m_pos;
	if (diff.Length() <= 2000.0f and diff.Length() >= 600.0f and m_player->m_swim == false) {
		m_modelRender.PlayAnimation(enAnimClip_Chase);
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
	if (diff.Length() <= 1000.0f and diff.Length() >= 600.0f and m_player->m_swim == false) {
		m_oldPos = m_pos;
		m_characterController.SetPosition(m_ninjaPengin->m_pos);
		m_change = true;
	}
	
	else {
		m_rot.SetRotationDegY(180.0f);
	}

	moveSpeed.y = 0.0f;
	moveSpeed.z -= 1.0f;
	m_pos = m_characterController.Execute(moveSpeed, 1.0f);
	m_modelRender.SetRotation(m_rot);
	m_modelRender.SetPosition(m_pos);

	m_modelRender.Update();
}

void  Dummy::Render(RenderContext& rc) {
	m_modelRender.Draw(rc);

}
