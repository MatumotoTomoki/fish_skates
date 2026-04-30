#include "stdafx.h"
#include "Player.h"
#include "Pengin.h"
#include "NinjaPengin.h"
#include "SilenPengin.h"
#include "Dummy5.h"
#include "Pause.h"

bool Player::Start() {
	m_characterController.Init(25.0f, 75.0f, m_position);
	m_animationClips[enAnimClip_Idle].Load("Assets/animdata/fish_idol.tka");
	m_animationClips[enAnimClip_Idle].SetLoopFlag(true);
	m_animationClips[enAnimClip_Jump].Load("Assets/animdata/fish_jump.tka");
	m_animationClips[enAnimClip_Jump].SetLoopFlag(false);
	m_animationClips[enAnimClip_Swim].Load("Assets/animdata/fish_swim2.tka");
	m_animationClips[enAnimClip_Swim].SetLoopFlag(true);
	m_animationClips[enAnimClip_WaterJump].Load("Assets/animdata/fish_waterJump.tka");
	m_animationClips[enAnimClip_WaterJump].SetLoopFlag(false);
	m_modelRender.Init("Assets/modelData/fish_idol.tkm", m_animationClips, enAnimClip_Num, enModelUpAxisZ);
	m_effectEmitter = NewGO <EffectEmitter>(0);
	m_effectEmitter->Init(1);
	m_effectEmitter->SetScale({ 90.0f,90.0f,90.0f });
	m_effectEmitter->Play();
	m_modelRender.SetScale(10.0f, 10.0f, 10.0f);
	m_sprite.Init("Assets/sprite/931912.dds",150.0f,150.0f);
	m_sprite.SetPosition({ 0.0f,-300.0f,0.0f });
	m_sprite.Update();
	m_rot.SetRotationDegZ(-90.0f);
	m_modelRender.SetRotation(m_rot);
	m_pengin = FindGO<Pengin>("Pengin");
	m_ninjaPengin = FindGO<NinjaPengin>("NinjaPengin");
	m_silenPengin = FindGO<SilenPengin>("SilenPengin");
	m_dummy5 = FindGO<Dummy5>("Dummy5");
	m_modelRender.Update();
	return true;
}

void Player::Update() {
	auto pause = FindGO<Pause>("Pause");
	if (pause && pause->IsPaused()) {
		return;
	}
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
	m_diff4 = m_position - m_dummy5->m_pos;
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
		else if (m_waterJump == true) {
			m_velocity += cameraForward * speed;
		}
	}
	else {
		m_superJump = false;
		m_modelRender.PlayAnimation(enAnimClip_Idle);
	}
	if (m_characterController.IsOnGround() == true or m_swim == true) {
		if (m_diff.Length() >= 600.0f and m_diff2.Length() >= 600.0f and m_diff3.Length() >= 600.0f and m_diff4.Length() >= 600.0f) {
			if (g_pad[0]->IsTrigger(enButtonA)) {
				auto eff = NewGO<EffectEmitter>(0);
				eff->Init(2);
				eff->SetScale({ 10.0f,1.0f,10.0f });
				eff->SetPosition(m_position);
				eff->Play();
				m_velocity.y = 12.0f;
			}
		}
		if (m_i < 0) {
			m_sprite.Init("Assets/sprite/931912.dds", 150.0f, 150.0f);
			m_sprite.SetPosition({ 0.0f,-300.0f,0.0f });
			m_sprite.Update();
			m_i++;
		}
	}
	if (m_characterController.IsOnGround() == true) {
		if (m_swim == false) {
			m_eff = 0;
			m_effectEmitter->SetPosition({90000.0f,0.0f,0.0f});
			m_se = 0;
		}
		m_waterJump = false;
	}
	else {
		if (m_diff.Length() >= 600.0f and m_diff2.Length() >= 600.0f and m_diff3.Length() >= 600.0f and m_diff4.Length() >= 600.0f) {
			if (m_swim == true) {
				if (g_pad[0]->IsTrigger(enButtonA)) {
					m_swim = false;
					m_waterJump = true;
					m_modelRender.PlayAnimation(enAnimClip_WaterJump);
				}
			}
		}
		m_i -= 1;
		m_velocity.y -= 0.5f;
	}
	if (g_pad[0]->IsTrigger(enButtonLeft) and m_characterController.IsOnGround() == true) {
		if (m_diff.Length() <= 600.0f or m_diff2.Length() <= 600.0f or m_diff3.Length() <= 600.0f or m_diff4.Length() <= 600.0f) {
			m_superJump = true;
			m_velocity.x -= 300.0f;
			m_velocity.y += 25.0f;
			m_sprite.Init("Assets/sprite/931908.dds", 200.0f, 150.0f);
			m_sprite.SetPosition({ -25.0f,-300.0f,0.0f });
			auto eff = NewGO<EffectEmitter>(0);
			eff->Init(2);
			eff->SetScale({ 10.0f,1.0f,10.0f });
			eff->SetPosition(m_position);
			eff->Play();
			m_sprite.Update();
		}
	}
	if (g_pad[0]->IsTrigger(enButtonRight) and m_characterController.IsOnGround() == true) {
		if (m_diff.Length() <= 600.0f or m_diff2.Length() <= 600.0f or m_diff3.Length() <= 600.0f or m_diff4.Length() <= 600.0f) {
			m_superJump = true;
			m_velocity.y += 25.0f;
			m_velocity.x += 300.0f;
			m_sprite.Init("Assets/sprite/931902.dds", 200.0f, 150.0f);
			m_sprite.SetPosition({ 25.0f,-300.0f,0.0f });
			auto eff = NewGO<EffectEmitter>(0);
			eff->Init(2);
			eff->SetScale({ 10.0f,1.0f,10.0f });
			eff->SetPosition(m_position);
			eff->Play();
			m_sprite.Update();
		}
	}
	if (g_pad[0]->IsTrigger(enButtonUp) and m_characterController.IsOnGround() == true) {
		if (m_diff.Length() <= 600.0f or m_diff2.Length() <= 600.0f or m_diff3.Length() <= 600.0f or m_diff4.Length() <= 600.0f) {
			m_superJump = true;
			m_velocity.y += 25.0f;
			m_sprite.Init("Assets/sprite/931911.dds", 150.0f, 200.0f);
			m_sprite.SetPosition({ 0.0f,-275.0f,0.0f });
			auto eff = NewGO<EffectEmitter>(0);
			eff->Init(2);
			eff->SetScale({ 10.0f,1.0f,20.0f });
			eff->SetPosition(m_position);
			eff->Play();
			m_sprite.Update();
		}
	}
	if (g_pad[0]->IsTrigger(enButtonDown) and m_characterController.IsOnGround() == true) {
		if (m_diff.Length() <= 600.0f or m_diff2.Length() <= 600.0f or m_diff3.Length() <= 600.0f or m_diff4.Length() <= 600.0f) {
			m_superJump = true;
			m_velocity.z -= 10.0f;
			m_velocity.y += 20.0f;
			m_sprite.Init("Assets/sprite/931905.dds", 150.0f, 200.0f);
			m_sprite.SetPosition({ 0.0f,-325.0f,0.0f });
			auto eff = NewGO<EffectEmitter>(0);
			eff->Init(2);
			eff->SetScale({ 10.0f,1.0f,10.0f });
			eff->SetPosition(m_position);
			eff->Play();
			m_sprite.Update();
		}
	}
	if (m_position.y <= -30.0f) {
		m_o2 -= 0.01f;
		m_swim = true;
		m_position.y = -30.0f;
		if (m_waterJump == false) {
			m_velocity.y = 0.2f;
		}
	}
	if (m_swim == true) {
		if (m_eff < 12) {
			m_effectEmitter->SetPosition({ m_position.x,m_posy,m_position.z });
			m_posy += 100.0f;
			m_eff++;
		}
		if (m_eff > 11) {
			m_effectEmitter->SetPosition({ 90000.0f,0.0f,0.0f });
			m_posy = -100.0f;
		}
		if (m_se == 0) {
			SoundSource* se = NewGO<SoundSource>(0);
			se->Init(7);
			se->Play(false);
			float finalSE = (pause->m_sevolume / 10.0f) * (pause->m_master / 10.0f);
			se->SetVolume(finalSE);
			m_se++;
		}
		if (m_se <= 1) {
			if (g_pad[0]->IsTrigger(enButtonA)) {
				m_se = 0;
			}
		}
		if (m_waterJump == false) {
			m_count += 0.1f;
			m_modelRender.PlayAnimation(enAnimClip_Swim);
		}
		m_rot.SetRotationDegZ(0.0f);
		if (m_characterController.IsOnGround() == true) {
			m_swim = false;
		}
		m_i -= 1;
	}
	else {
		m_count = 0.0f;
		if (m_diff.Length() <= 350.0f) {
			m_hp += 0.01f;
		}
		if (m_diff2.Length() <= 350.0f) {
			m_hp += 0.01f;
		}
		if (m_diff3.Length() <= 350.0f) {
			m_hp += 0.01f;
		}
		if (m_diff4.Length() <= 350.0f) {
			m_hp += 0.01f;
		}
		m_rot.SetRotationDegZ(-90.0f);
	}
	if (m_count >= 20.0f) {
		m_waterJump = true;
		m_modelRender.PlayAnimation(enAnimClip_WaterJump);
		m_se = 0;
		m_velocity.y += 20.0f;
		m_count = 0.0f;
	}
	m_position.y += 12.0f;
	if (m_o2 <= -1.05f) {
		m_o2 = -1.05f;
	}
	if (m_i < -1) {
		m_i = -1;
	}
	if (g_pad[0]->IsPress(enButtonY)) {
		m_o2 -= 0.002f;
		m_hp += 0.003f;
	}
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetRotation(m_rot);
	m_position = m_characterController.Execute(m_velocity, 1.0f);
	m_modelRender.Update();
}

void Player::Render(RenderContext& rc) {
	m_modelRender.Draw(rc);
	if (m_diff.Length() <= 600.0f or m_diff2.Length() <= 600.0f or m_diff3.Length() <= 600.0f or m_diff4.Length() <= 600.0f) {
		m_sprite.Draw(rc);
	}
}
