#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"
#include "Pause.h"

bool GameCamera::Start() {
	m_toCameraPos.Set(0.0f, 0.0f, -500.0f);
	m_player = FindGO<Player>("Player");
	g_camera3D->SetNear(1.0f);
	g_camera3D->SetFar(20000.0f);
	return true;
}

void GameCamera::Update() {
    auto pause = FindGO<Pause>("Pause");
    if (pause && pause->IsPaused()) {
        return;
    }

    Vector3 playerRawTarget = m_player->m_position;
    playerRawTarget.y += 80.0f;

    float lerpFactor = 0.8f;
    m_currentCameraTarget.Lerp(lerpFactor, m_currentCameraTarget, playerRawTarget);

    float x = g_pad[0]->GetRStickXF();
    float y = g_pad[0]->GetRStickYF();

    Quaternion qRot;
    Vector3 dir = m_toCameraPos;

    // --- 左右回転 ---
    Vector3 oldPosYaw = m_toCameraPos;

    qRot.SetRotationDeg(Vector3::AxisY, -1.3f * x);
    qRot.Apply(m_toCameraPos);

    // 左右制限チェック（水平成分で判定）
    Vector3 horizontalDir = m_toCameraPos;
    horizontalDir.y = 0;

    float len = horizontalDir.Length();   // ← これが必要！

    if (len > 0.001f) {
        horizontalDir /= len;

        if (horizontalDir.x < -0.8f or horizontalDir.x > 0.8f) {
            m_toCameraPos = oldPosYaw;
        }
    }

    // --- 上下回転 ---
    Vector3 oldPosPitch = m_toCameraPos;

    // 上下回転の軸
    Vector3 axisX;
    axisX.Cross(Vector3::AxisY, m_toCameraPos);
    axisX.Normalize();

    qRot.SetRotationDeg(axisX, -1.3f * y);

    qRot.Apply(m_toCameraPos);

    // 上下制限チェック
    dir = m_toCameraPos;
    dir.Normalize();
    if (dir.y < -0.15f or dir.y > 0.9f) {
        m_toCameraPos = oldPosPitch;
    }

    // カメラ位置更新
    Vector3 pos = m_currentCameraTarget + m_toCameraPos;

    g_camera3D->SetTarget(m_currentCameraTarget);
    g_camera3D->SetPosition(pos);
    g_camera3D->Update();
}
