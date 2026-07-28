#include "stdafx.h"
#include "ReversePengin.h"
#include "Player.h"
#include "Pause.h"
#include <time.h>

bool ReversePengin::Start() {
	// 乱数初期化（本当はゲーム開始時に1回だけが理想）
	srand((unsigned int)time(NULL));
	m_animationClips[enAnimClip_Walk].Load("Assets/animData/pengin_walk.tka");
	m_animationClips[enAnimClip_Walk].SetLoopFlag(true);
	m_animationClips[enAnimClip_Chase].Load("Assets/animData/pengin_chase.tka");
	m_animationClips[enAnimClip_Chase].SetLoopFlag(false);
	m_animationClips[enAnimClip_Attack].Load("Assets/animData/pengin_attack.tka");
	m_animationClips[enAnimClip_Attack].SetLoopFlag(true);
	m_modelRender.Init(
		"Assets/modelData/superPen.tkm",
		m_animationClips,
		enAnimClip_Num,
		enModelUpAxisZ
	);
	// ランダムスポーン
	m_player = FindGO<Player>("Player");
	if (m_player != nullptr) {
		Vector3 forward = g_camera3D->GetForward();
		forward.y = 0.0f;
		forward.Normalize();
		// プレイヤー前方1500～3500
		float forwardDist = rand() % 1500 + 3000;
		// 左右に±500
		Vector3 right;
		right.Cross(Vector3::AxisY, forward);
		right.Normalize();
		float sideOffset = rand() % 1000 - 300;
		m_pos = m_player->m_position + forward * forwardDist + right * sideOffset;
		m_pos.y = 10.0f;
	}
	m_modelRender.SetScale(15.0f, 15.0f, 15.0f);
	m_modelRender.SetPosition(m_pos);
	m_modelRender.SetRotation(m_rot);
	m_modelRender.Update();
	return true;
}

void ReversePengin::Update() {
	auto pause = FindGO<Pause>("Pause");
	if (pause and pause->IsPaused()) {
		return;
	}
	Vector3 moveSpeed;
	if (m_player == nullptr) {
		m_player = FindGO<Player>("Player");
		if (m_player == nullptr) {
			return;
		}
	}
	Vector3 diff = m_player->m_position - m_pos;
	//プレイヤーへの攻撃
	if (diff.Length() <= 350.0f) {
		m_modelRender.PlayAnimation(enAnimClip_Attack);
	}
	// プレイヤー追跡
	else if (diff.Length() <= 2000.0f and diff.Length()>= 600.0f and m_player->m_swim == false) {
		m_modelRender.PlayAnimation(enAnimClip_Chase);
		Vector3 toPlayerDir = diff;
		toPlayerDir.Normalize();
		if (m_player->m_superJump == false) {
			moveSpeed += toPlayerDir * 15.0f;
			float angleY = atan2f(toPlayerDir.x, toPlayerDir.z);
			m_rot.SetRotationY(angleY);
		}
		else {
			moveSpeed.z -= 15.0f;
		}
	}
	else if (diff.Length() <= 600.0f and m_player->m_swim == false) {
		Vector3 toPlayerDir = diff;
		toPlayerDir.Normalize();
		if (m_player->m_superJump == false) {
			moveSpeed += toPlayerDir * 0.6f;
			float angleY = atan2f(toPlayerDir.x, toPlayerDir.z);
			m_rot.SetRotationY(angleY);
		}
		else {
			float angleY = atan2f(toPlayerDir.x, toPlayerDir.z);
			m_rot.SetRotationY(angleY);
			Vector3 forward;
			forward.x = sinf(angleY);
			forward.y = 0.0f;
			forward.z = cosf(angleY);
			moveSpeed += forward * 8.0f;
		}
	}
	// プレイヤー泳ぎ中
	else if (m_player->m_swim == true) {
		Vector3 toPlayerDir = diff;
		float angleY = atan2f(toPlayerDir.x, toPlayerDir.z);
		m_rot.SetRotationY(angleY);
	}
	// 通常移動
	else {
		m_modelRender.PlayAnimation(enAnimClip_Walk);
		m_rot.SetRotationDegY(180.0f);
		moveSpeed.z -= 1.0f;
	}
	moveSpeed.y = 0.0f;
	m_pos += moveSpeed;
	m_modelRender.SetRotation(m_rot);
	m_modelRender.SetPosition(m_pos);
	m_modelRender.Update();
}

void ReversePengin::Render(RenderContext& rc) {
	m_modelRender.Draw(rc);
}