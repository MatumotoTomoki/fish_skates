#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"
#include "Pause.h"
#include "Title.h"

bool GameCamera::Start() {
    m_toCameraPos.Set(0.0f, 0.0f, -570.0f);
    // ★ カメラの向きと注視点を初期化
    Vector3 target = { 0.0f, 80.0f, 9000.0f };
    g_camera3D->SetTarget(target);
    g_camera3D->SetPosition(m_toCameraPos.x, 60.0f, m_toCameraPos.z);
    g_camera3D->SetNear(1.0f);
    g_camera3D->SetFar(20000.0f);
    auto title = FindGO<Title>("Title");
    if (title->m_specialCamera == false) {
        m_special = false;
    }
    else {
        m_special = true;
    }
    return true;
}

void GameCamera::Update() {
    auto pause = FindGO<Pause>("Pause");
    if (pause and pause->IsPaused()) {
        return;
    }
    auto title = FindGO<Title>("Title");
    if (title) {
        return;
    }
    if (m_player == nullptr) {
        m_player = FindGO<Player>("Player");
    }
        Vector3 playerRawTarget = m_player->m_position;
        playerRawTarget.y += 80.0f;
        float lerpFactor = 0.8f;
        m_currentCameraTarget.Lerp(lerpFactor, m_currentCameraTarget, playerRawTarget);
    if (m_player->m_start == true) {
        // ★ ここが“本命”のリセットポイント
        if (m_resetOnStart) {
            // 角度・距離・注視点を毎ループ同じ状態に戻す
            m_toCameraPos.Set(0.0f, 0.0f, 7000.0f);
            m_currentCameraTarget = m_player->m_position;
            m_currentCameraTarget.y += 80.0f;
            m_resetOnStart = false;
        }
        // ここから先は今まで通り
        if (m_toCameraPos.z >= -170.0f) {
            m_zoom = false;
        }
        if (m_zoom == false and m_toCameraPos.z > -370.0f) {
            if (m_flug == false) {
                m_toCameraPos.z -= 33.0f;
            }
        }
        else if (m_zoom == false and m_toCameraPos.z < -370.0f) {
            m_flug = true;
        }
        if (m_flug == true) {
            float x = g_pad[0]->GetRStickXF();
            float y = g_pad[0]->GetRStickYF();
            Quaternion qRot;
            Vector3 dir = m_toCameraPos;
            Vector3 oldPosYaw = m_toCameraPos;
            if (m_special == false) {
                qRot.SetRotationDeg(Vector3::AxisY, -1.3f * x);
            }
            else {
                qRot.SetRotationDeg(Vector3::AxisY, 1.3f * x);
            }
            qRot.Apply(m_toCameraPos);
            Vector3 horizontalDir = m_toCameraPos;
            horizontalDir.y = 0;
            float len = horizontalDir.Length();
            if (len > 0.001f) {
                horizontalDir /= len;
                if (horizontalDir.x < -0.999f or horizontalDir.x > 0.999f) {
                    m_toCameraPos = oldPosYaw;
                }
            }
            Vector3 oldPosPitch = m_toCameraPos;
            Vector3 axisX;
            axisX.Cross(Vector3::AxisY, m_toCameraPos);
            axisX.Normalize();
            if (m_special == false) {
                qRot.SetRotationDeg(axisX, -1.3f * y);
            }
            else {
                qRot.SetRotationDeg(axisX, 1.3f * y);
            }
            qRot.Apply(m_toCameraPos);
            dir = m_toCameraPos;
            dir.Normalize();
            if (dir.y < -0.15f or dir.y > 0.9f) {
                m_toCameraPos = oldPosPitch;
            }
        }
        Vector3 pos = m_currentCameraTarget + m_toCameraPos;
        if (m_flug == true) {
            g_camera3D->SetTarget(m_currentCameraTarget);
        }
        g_camera3D->SetPosition(pos);
        g_camera3D->Update();
    }
}
