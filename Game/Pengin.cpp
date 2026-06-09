#include "stdafx.h"
#include "Pengin.h"
#include "Player.h"
#include "Pause.h"
#include <time.h>

bool Pengin::Start() {

	// 乱数初期化（本当はゲーム開始時に1回だけが理想）
	srand((unsigned int)time(NULL));

	m_animationClips[enAnimClip_Walk].Load("Assets/animData/pengin_walk.tka");
	m_animationClips[enAnimClip_Walk].SetLoopFlag(true);

	m_animationClips[enAnimClip_Chase].Load("Assets/animData/pengin_chase.tka");
	m_animationClips[enAnimClip_Chase].SetLoopFlag(false);

	m_modelRender.Init(
		"Assets/modelData/pengin.tkm",
		m_animationClips,
		enAnimClip_Num,
		enModelUpAxisZ
	);

	// ランダムスポーン
	m_player = FindGO<Player>("Player");

if (m_player != nullptr)
{
    Vector3 forward = g_camera3D->GetForward();
    forward.y = 0.0f;
    forward.Normalize();

    // プレイヤー前方2000～3000
    float forwardDist = rand() % 1000 + 2000;

    // 左右に±500
    Vector3 right;
    right.Cross(Vector3::AxisY, forward);
    right.Normalize();

    float sideOffset = rand() % 2000 - 1000;

    m_pos =
        m_player->m_position +
        forward * forwardDist +
        right * sideOffset;

    m_pos.y = 40.0f;
}

	m_modelRender.SetScale(15.0f, 15.0f, 15.0f);
	m_modelRender.SetPosition(m_pos);
	m_modelRender.SetRotation(m_rot);

	m_characterController.Init(75.0f, 75.0f, m_pos);

	m_modelRender.Update();

	return true;
}

void Pengin::Update() {

	auto pause = FindGO<Pause>("Pause");
	if (pause && pause->IsPaused()) {
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

	// プレイヤー追跡
	if (diff.Length() <= 2000.0f &&
		diff.Length() >= 600.0f &&
		m_player->m_swim == false)
	{
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

	// 近距離
	else if (diff.Length() <= 600.0f &&
		m_player->m_swim == false)
	{
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

		Vector3 diff = m_pos - m_player->m_position;

		Vector3 toPlayerDir = diff;
		toPlayerDir.Normalize();

		moveSpeed += toPlayerDir * 5.0f;
	}

	// 通常移動
	else {

		m_modelRender.PlayAnimation(enAnimClip_Walk);

		m_rot.SetRotationDegY(180.0f);

		moveSpeed.z -= 1.0f;
	}

	moveSpeed.y = 0.0f;

	m_modelRender.SetRotation(m_rot);
	m_modelRender.SetPosition(m_pos);

	m_pos = m_characterController.Execute(moveSpeed, 1.0f);

	m_modelRender.Update();
}

void Pengin::Render(RenderContext& rc) {
	m_modelRender.Draw(rc);
}