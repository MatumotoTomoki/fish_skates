#include "stdafx.h"
#include "Pengin.h"
#include "Player.h"

bool Pengin::Start() {
	m_modelRender.Init("Assets/modelData/pennginnnn.tkm");
	m_pos = { 0.0f,0.0f,500.0f };
	m_modelRender.SetScale(10.0f, 10.0f, 10.0f);
	m_rot.SetRotationDegY(180.0f);
	m_modelRender.SetRotation(m_rot);
	m_modelRender.SetPosition(m_pos);
	m_player = FindGO<Player>("Player");
	return true;
}

void Pengin::Update() {
	Vector3 diff = m_player->m_position - m_pos;
	if (diff.Length() <= 1000.0f and m_player->m_swim == false) {
		float distToPlayer = diff.Length();

		Vector3 toPlayerDir = diff;
		toPlayerDir.Normalize();

		m_pos += toPlayerDir * 5.0f;

		float angleY = atan2f(toPlayerDir.x, toPlayerDir.z);

		// ラジアンを度数に変換し、回転行列を作成
		m_rot.SetRotationY(angleY);
		
	}
	else if (m_player->m_swim == true) {
		Vector3 diff = m_pos - m_player->m_position;
		float distToPlayer = diff.Length();

		Vector3 toPlayerDir = diff;
		toPlayerDir.Normalize();

		m_pos += toPlayerDir * 5.0f;

		float angleY = atan2f(toPlayerDir.x, toPlayerDir.z);
		m_rot.SetRotationY(-angleY);
	}
	else {
		m_rot.SetRotationDegY(180.0f);
	}
	m_pos.y = 0.0f;
	m_pos.z -= 1.0f;
	m_modelRender.SetRotation(m_rot);
	m_modelRender.SetPosition(m_pos);
	m_modelRender.Update();
}

void Pengin::Render(RenderContext& rc) {
	m_modelRender.Draw(rc);
}