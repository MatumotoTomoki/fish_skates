#include "stdafx.h"
#include "Player.h"
#include "Pengin.h"

bool Player::Start() {
	m_characterController.Init(25.0f, 75.0f, m_position);
	m_animationClips[enAnimClip_Idle].Load("assets/animdata/fish_idol.tka");
	m_animationClips[enAnimClip_Idle].SetLoopFlag(true);
	m_animationClips[enAnimClip_Jump].Load("assets/animdata/fish_jump.tka");
	m_animationClips[enAnimClip_Jump].SetLoopFlag(false);
	m_animationClips[enAnimClip_Swim].Load("assets/animdata/fish_swim2.tka");
	m_animationClips[enAnimClip_Swim].SetLoopFlag(true);
	m_animationClips[enAnimClip_WaterJump].Load("assets/animdata/fish_waterJump.tka");
	m_animationClips[enAnimClip_WaterJump].SetLoopFlag(false);
	m_modelRender.Init("Assets/modelData/fish_idol.tkm", m_animationClips, enAnimClip_Num, enModelUpAxisZ);
	m_modelRender.SetScale(10.0f, 10.0f, 10.0f);
	m_rot.SetRotationDegZ(-90.0f);
	m_modelRender.SetRotation(m_rot);
	m_pengin = FindGO<Pengin>("Pengin");
	m_modelRender.Update();
	return true;
}

void Player::Update() {
	m_velocity.x = 0.0f;
	m_velocity.z = 0.0f;
	if (m_characterController.IsOnGround() == false) {
		if (m_swim == false and m_waterJump == false) {
			m_modelRender.PlayAnimation(enAnimClip_Jump);
			m_velocity.z += 5.0f;
		}
		if (m_waterJump == true) {
			m_velocity.z += 5.0f;
		}

	}
	else {
		m_modelRender.PlayAnimation(enAnimClip_Idle);
	}
	if (m_characterController.IsOnGround() == true or m_swim == true)  {
		if (g_pad[0]->IsTrigger(enButtonA)) {
			m_velocity.y = 15.0f;
			if (m_swim == true) {
				if (m_characterController.IsOnGround() == false) {
					m_waterJump = true;
					m_swim = false;
				}
				m_modelRender.PlayAnimation(enAnimClip_WaterJump);
			}
		}
	}
	if (m_characterController.IsOnGround() == true) {
		m_waterJump = false;
	}
	else {
		m_velocity.y -= 0.5f;
	}
	if (g_pad[0]->IsPress(enButtonLeft)) {
		m_velocity.x -= 10.0f;
	}
	if (g_pad[0]->IsPress(enButtonRight)) {
		m_velocity.x += 10.0f;
	}
	if (g_pad[0]->IsPress(enButtonUp)) {
		m_velocity.z += 10.0f;
	}
	if (g_pad[0]->IsPress(enButtonDown)) {
		m_velocity.z -= 10.0f;
	}
	if (m_position.y <= -30.0f) {
		m_swim = true;
		m_position.y = -30.0f;
		if (m_waterJump == false) {
			m_velocity.y = 0.1f;
		}
	}
	if (m_swim == true) {
		if (m_waterJump == false) {
			//m_velocity.y = 0.0f;
			m_modelRender.PlayAnimation(enAnimClip_Swim);
		}
		m_rot.SetRotationDegZ(0.0f);
		if (m_characterController.IsOnGround() == true) {
			m_swim = false;
		}
	}
	else {
		m_rot.SetRotationDegZ(-90.0f);
	}
	m_position.y += 8.0f;
	Vector3 diff = m_pengin->m_pos - m_position;

	if (diff.Length() <= 300.0f) {
		float distToPlayer = diff.Length();

		Vector3 toPlayerDir = diff;
		toPlayerDir.Normalize();

		m_position += toPlayerDir * 50.0f;

		float angleY = atan2f(toPlayerDir.x, toPlayerDir.z);
		m_rot.SetRotationY(-angleY);
	}
	wchar_t shineText[64];
	swprintf(shineText, 64, L"力:%.0f", m_position.y);
	m_font.SetText(shineText);
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetRotation(m_rot);
	m_position = m_characterController.Execute(m_velocity, 1.0f);
	m_modelRender.Update();
}

void Player::Render(RenderContext& rc) {
	m_modelRender.Draw(rc);
	//m_font.Draw(rc);
}