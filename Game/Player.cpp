#include "stdafx.h"
#include "Player.h"
#include "Pengin.h"
#include "NinjaPengin.h"
#include "SilenPengin.h"

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
	m_sprite.Init("Assets/sprite/931912.dds",150.0f,150.0f);
	m_sprite.SetPosition({ 0.0f,-300.0f,0.0f });
	m_sprite.Update();
	m_rot.SetRotationDegZ(-90.0f);
	m_modelRender.SetRotation(m_rot);
	m_pengin = FindGO<Pengin>("Pengin");
	m_ninjaPengin = FindGO<NinjaPengin>("NinjaPengin");
	m_silenPengin = FindGO<SilenPengin>("SilenPengin");
	m_modelRender.Update();
	return true;
}

void Player::Update() {
	m_o2 += 0.001f;
	Vector3 forward = g_camera3D->GetForward();
	// カメラの "前方向" ベクトルを、水平方向だけにしたベクトルを作成
	Vector3 cameraForward = forward;
	cameraForward.y = 0.0f; // Y成分（上下方向）をゼロにして、水平方向（地面に沿った方向）にする
	cameraForward.Normalize(); // ベクトルの長さを1に戻す
	// moveSpeedにカメラの前進方向の速度を加える
	float speed = 10.0f;

	m_diff = m_position - m_pengin->m_pos;
	m_diff2 = m_position - m_ninjaPengin->m_pos;
	m_diff3 = m_position - m_silenPengin->m_pos;

	if (m_o2 > -0.1f) {
		m_o2 = -0.1f;
	}
	m_velocity.x = 0.0f;
	m_velocity.z = 0.0f;
	if (m_characterController.IsOnGround() == false) {
		if (m_swim == false and m_waterJump == false) {
			m_modelRender.PlayAnimation(enAnimClip_Jump);
			m_velocity += cameraForward * speed;
		}
		if (m_waterJump == true) {
			m_velocity += cameraForward * speed;
		}

	}
	else {
		m_superJump = false;
		m_modelRender.PlayAnimation(enAnimClip_Idle);
	}
	if (m_characterController.IsOnGround() == true or m_swim == true) {
		if (g_pad[0]->IsTrigger(enButtonA)) {
			m_velocity.y = 12.0f;
			if (m_swim == true) {
				if (m_characterController.IsOnGround() == false) {
					m_waterJump = true;
					m_swim = false;
				}
				m_modelRender.PlayAnimation(enAnimClip_WaterJump);
			}
		}
		for (; m_i < 0; m_i++) {
			m_sprite.Init("Assets/sprite/931912.dds", 150.0f, 150.0f);
			m_sprite.SetPosition({ 0.0f,-300.0f,0.0f });
			m_sprite.Update();
		}
	}
	if (m_characterController.IsOnGround() == true) {
		m_waterJump = false;
	}
	else {
		m_i -= 1;
		m_velocity.y -= 0.5f;
	}
	if (g_pad[0]->IsTrigger(enButtonLeft) and m_characterController.IsOnGround() == true) {
		m_superJump = true;
		m_velocity.x -= 300.0f;
		m_velocity.y += 20.0f;
		m_sprite.Init("Assets/sprite/931908.dds", 200.0f, 150.0f);
		m_sprite.SetPosition({ -25.0f,-300.0f,0.0f });
		m_sprite.Update();
	}
	if (g_pad[0]->IsTrigger(enButtonRight) and m_characterController.IsOnGround() == true) {
		m_superJump = true;
		m_velocity.y += 20.0f;
		m_velocity.x += 300.0f;
		m_sprite.Init("Assets/sprite/931902.dds", 200.0f, 150.0f);
		m_sprite.SetPosition({ 25.0f,-300.0f,0.0f });
		m_sprite.Update();
	}
	if (g_pad[0]->IsTrigger(enButtonUp) and m_characterController.IsOnGround() == true) {
		m_superJump = true;
		m_velocity.y += 25.0f;
		m_sprite.Init("Assets/sprite/931911.dds", 150.0f, 200.0f);
		m_sprite.SetPosition({ 0.0f,-275.0f,0.0f });
		m_sprite.Update();
	}
	if (g_pad[0]->IsTrigger(enButtonDown) and m_characterController.IsOnGround() == true) {
		m_superJump = true;
		m_velocity.z -= 10.0f;
		m_velocity.y += 20.0f;
		m_sprite.Init("Assets/sprite/931905.dds", 150.0f, 200.0f);
		m_sprite.SetPosition({ 0.0f,-325.0f,0.0f });
		m_sprite.Update();
	}
	if (m_position.y <= -30.0f) {
		m_o2 -= 0.01f;
		m_swim = true;
		m_position.y = -30.0f;
		if (m_waterJump == false) {
			m_velocity.y = 0.1f;
		}
	}
	if (m_swim == true) {
		if (m_waterJump == false) {
			m_modelRender.PlayAnimation(enAnimClip_Swim);
		}
		m_rot.SetRotationDegZ(0.0f);
		if (m_characterController.IsOnGround() == true) {
			m_swim = false;
		}
		m_i -= 1;
	}
	else {
		if (m_diff.Length() <= 350.0f) {
			m_hp += 0.001f;
		}
		if (m_diff2.Length() <= 350.0f) {
			m_hp += 0.001f;
		}
		if (m_diff3.Length() <= 350.0f) {
			m_hp += 0.01f;
		}
		m_rot.SetRotationDegZ(-90.0f);
	}
	m_position.y += 12.0f;

	if (m_o2 <= -1.05f) {
		m_o2 = -1.05f;
	}

	if (m_i < -1) {
		m_i = -1;
	}

	m_modelRender.SetPosition(m_position);
	m_modelRender.SetRotation(m_rot);
	m_position = m_characterController.Execute(m_velocity, 1.0f);
	m_modelRender.Update();
}

void Player::Render(RenderContext& rc) {
	m_modelRender.Draw(rc);
	if (m_diff.Length() <= 600.0f or m_diff2.Length() <= 600.0f or m_diff3.Length() <= 600.0f) {
		m_sprite.Draw(rc);
	}
}
