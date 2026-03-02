#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"
#include "Game.h"

bool GameCamera::Start() {
	m_toCameraPos.Set(0.0f, 0.0f, -500.0f);
	m_player = FindGO<Player>("Player");
	g_camera3D->SetNear(1.0f);
	g_camera3D->SetFar(20000.0f);
	return true;
}

void GameCamera::Update() {
	Vector3 playerRawTarget = m_player->m_position; // プレイヤーの現在位置を取得
	playerRawTarget.y += 80.0f; // 目標Y座標を調整
	float lerpFactor = 0.8f; // 追従の滑らかさを調整する係数 (0.0で動かない、1.0で即座に追従)
	// ★ここを修正するよ★
	// m_currentCameraTarget のメソッドとして Lerp を呼び出す
	// そして、引数の順序を (t, v0, v1) に合わせる
	// v0 (開始点) は m_currentCameraTarget 自身、v1 (終了点) は playerRawTarget
	// この Lerp 関数は戻り値が void で、呼び出し元のオブジェクト (m_currentCameraTarget) 自身を更新する設計だね。
	m_currentCameraTarget.Lerp(lerpFactor, m_currentCameraTarget, playerRawTarget);
	Vector3 toCameraPosOld = m_toCameraPos;
	
		float x = g_pad[0]->GetRStickXF();
		float y = g_pad[0]->GetRStickYF();

		Quaternion qRot;
		qRot.SetRotationDeg(Vector3::AxisY, -1.3f * x);
		qRot.Apply(m_toCameraPos);
		Vector3 axisX;
		if (m_cameraUp == false) {
			axisX.Cross(Vector3::AxisY, m_toCameraPos);
		}
		axisX.Normalize();
		if (m_cameraUp == false) {
			qRot.SetRotationDeg(axisX, -1.3f * y);
		}
		if (m_cameraUp == true) {
			qRot.SetRotationDeg(axisX, y);
		}
		qRot.Apply(m_toCameraPos);
		Vector3 toPosDir = m_toCameraPos;
		toPosDir.Normalize();
		if (toPosDir.y < -0.9f) {
			m_toCameraPos = toCameraPosOld;
		}
		else if (toPosDir.y > 0.9f) {
			m_toCameraPos = toCameraPosOld;
		}
	
	// カメラの位置とターゲットに、補間された m_currentCameraTarget を使用
	Vector3 pos = m_currentCameraTarget + m_toCameraPos;
	if (g_pad[0]->IsTrigger(enButtonY)) {
		m_cameraUp = !m_cameraUp;
	}
	if (m_cameraUp == true) {
		// 【俯瞰視点モード】
		// ターゲット（プレイヤー）の真上に配置する
		pos.y = playerRawTarget.y += 2000.0f; // 高さはお好みで調整
	}

	g_camera3D->SetTarget(m_currentCameraTarget);
	g_camera3D->SetPosition(pos);
	g_camera3D->Update();
}

