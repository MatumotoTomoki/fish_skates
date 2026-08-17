#include "stdafx.h"
#include "Player.h"
#include "Pengin.h"
#include "NinjaPengin.h"
#include "SilenPengin.h"
#include "Dummy5.h"
#include "Pause.h"
#include "GameCamera.h"
#include "Item.h"
#include "Item2.h"
#include "Item3.h"
#include "Distance.h"
#include "ReversePengin.h"
#include "UI.h"

bool Player::Start() {
	m_animationClips[enAnimClip_Idle].Load("Assets/animdata/fish_idol.tka");
	m_animationClips[enAnimClip_Idle].SetLoopFlag(true);
	m_animationClips[enAnimClip_Jump].Load("Assets/animdata/fish_jump.tka");
	m_animationClips[enAnimClip_Jump].SetLoopFlag(false);
	m_animationClips[enAnimClip_Swim].Load("Assets/animdata/fish_swim2.tka");
	m_animationClips[enAnimClip_Swim].SetLoopFlag(true);
	m_animationClips[enAnimClip_WaterJump].Load("Assets/animdata/fish_waterJump.tka");
	m_animationClips[enAnimClip_WaterJump].SetLoopFlag(false);
	m_modelRender.Init("Assets/modelData/fish_idol.tkm", m_animationClips, enAnimClip_Num, enModelUpAxisZ);
	m_modelRender.SetScale(15.0f, 15.0f, 15.0f);
	m_qte.SetScale({ 1.1f,1.1f,0.0f });
	m_sprite.Init("Assets/sprite/931912.dds", 150.0f, 150.0f);
	m_sprite.SetPosition({ 0.0f,-300.0f,0.0f });
	m_sprite.Update();
	m_vignette.Init("Assets/sprite/haikei.DDS", 1920.0f,1080.0f);
	m_vignette.Update();
	m_zone.Init("Assets/sprite/syutyu_0821.dds", 1920.0f, 1080.0f);
	m_zone.Update();
	m_rot.SetRotationDegZ(-90.0f);
	m_modelRender.SetRotation(m_rot);
	m_pengin = FindGO<Pengin>("Pengin");
	m_ninjaPengin = FindGO<NinjaPengin>("NinjaPengin");
	m_silenPengin = FindGO<SilenPengin>("SilenPengin");
	m_reversePengin = FindGO<ReversePengin>("ReversePengin");
	m_dummy5 = FindGO<Dummy5>("Dummy5");
	m_item = FindGO<Item>("item");
	m_item3=FindGO<Item3>("item3");
	m_position = { 0.0f,1000.0f,0.0f };
	m_modelRender.SetPosition(m_position);
	m_characterController.Init(35.0f, 30.0f, m_position);
	m_characterController.SetPosition(m_position);
	m_modelRender.Update();
	m_start = false;
	m_characterController.Execute(m_velocity, 0);
	m_qteGauge = 1.0f;
	m_gaugeCB.gaugeRate = 1.0f;
	SpriteInitData initData;
	initData.m_ddsFilePath[0] = "Assets/sprite/QTEGauge.dds";
	initData.m_fxFilePath = "Assets/shader/QTEGauge.fx";
	initData.m_width = 150;
	initData.m_height = 150;
	initData.m_expandConstantBuffer = &m_gaugeCB;
	initData.m_expandConstantBufferSize = sizeof(m_gaugeCB);
	m_qte.Init(initData);
	m_qte.SetPosition({ 0.0f,-300.0f,0.0f });
	m_qte.Update();
	return true;
}

Player::~Player() {
	if (m_eff2 != nullptr) {
		m_eff2->Stop();
	}
}

void Player::Update() {
	auto pause = FindGO<Pause>("Pause");
	if (pause and pause->IsPaused()) {
		return;
	}
	auto camera = FindGO<GameCamera>("GameCamera");
	auto ui = FindGO<UI>("ui");
	if (camera->m_flug == true and m_start == false) {
		m_velocity.y -= 0.5f;
		m_position.y += 12.0f;
		if (m_characterController.IsOnGround() == true and ui->m_countDown <= 0.2f) {
			if (m_go < 62) {
				m_go++;
			}
		}
		if (m_go > 60) {
			m_start = true;
		}
		m_modelRender.SetPosition(m_position);
		m_position = m_characterController.Execute(m_velocity, 1.0f);
		m_modelRender.Update();
	}
	if (m_start == true) {
		m_go++;
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
		m_diff5 = m_position - m_reversePengin->m_pos;
		m_isEnemyNear = (m_diff.Length() <= 600.0f or m_diff2.Length() <= 600.0f or m_diff3.Length() <= 600.0f or m_diff4.Length() <= 600.0f or m_diff5.Length() <= 600.0f);
		if (m_o2 > -0.1f) {
			m_o2 = -0.1f;
		}
		m_velocity.x = 0.0f;
		m_velocity.z = 0.0f;
		if (m_characterController.IsOnGround() == false) {
			m_efk = 1;
			if (m_swim == false and m_waterJump == false) {
				m_modelRender.PlayAnimation(enAnimClip_Jump);
				m_velocity += cameraForward * speed;
			}
			else if (m_waterJump == true) {
				m_velocity += cameraForward * speed;
			}
		}
		else {
			if (m_distance == nullptr) {
				m_distance = FindGO<Distance>("Distance");
			}
			if (m_distance != nullptr) {
				if (m_distance->m_stage == 0) {
					if (m_position.z >= 3155.0f and m_position.z <= 3900.0f and m_position.x >= 3017.0f and m_position.x <= 3700.0f) {
						m_slip = true;
					}
					else if (m_position.z >= 2827.0f and m_position.z <= 3900.0f and m_position.x >= 131.0f and m_position.x <= 1400.0f) {
						m_slip = true;
					}
					else {
						m_slip = false;
					}
				}
				else if (m_distance->m_stage == 1) {
					if (m_position.z >= 6006.0f and m_position.z <= 7120.0f and m_position.x >= 655.6f and m_position.x <= 2076.0f) {
						m_slip = true;
					}
					else {
						m_slip = false;
					}
					if (m_position.z >= 5838.0f and m_position.z <= 6129.0f and m_position.x >= 655.6f and m_position.x <= 2076.0f) {
						m_rSlip = true;
					}
					else {
						m_rSlip = false;
					}
				}
			}
			m_modelRender.PlayAnimation(enAnimClip_Idle);
			m_superJump = false;
			m_velocity.y = 0.0f;
		}
		if (camera->m_flug == true) {
			if (m_diff.Length() <= 600.0f or m_diff2.Length() <= 600.0f or m_diff3.Length() <= 600.0f or m_diff4.Length() <= 600.0f or m_diff5.Length() <= 600.0f) {
				m_o2 += 0.001f;
			}
			else {
				m_o2 += 0.002f;
			}
			if (m_characterController.IsOnGround() == true or m_swim == true) {
				if (m_diff.Length() >= 600.0f and m_diff2.Length() >= 600.0f and m_diff3.Length() >= 600.0f and m_diff4.Length() >= 600.0f and m_diff5.Length() >= 600.0f) {
					m_chase = false;
					if (g_pad[0]->IsTrigger(enButtonA)) {
						m_eff2 = NewGO<EffectEmitter>(0);
						m_eff2->Init(2);
						m_eff2->SetScale({ 10.0f,1.0f,10.0f });
						m_eff2->SetPosition(m_position);
						m_eff2->Play();
						SoundSource* se = NewGO<SoundSource>(0);
						se->Init(14);
						se->Play(false);
						float finalSE = (pause->m_sevolume / 10.0f) * (pause->m_master / 10.0f);
						se->SetVolume(finalSE);
						m_velocity.y = 12.0f;
					}
				}
				else {
					m_chase = true;
					m_modelRender.SetAnimationSpeed(0.6f);
				}
				if (m_efk == 1) {
					if (m_eff2 != nullptr) {
						m_eff2->Stop();
					}
					m_efk = 0;
				}
			}
			if (m_jump != 9) {
				if (m_superJump == true) {
					m_jump = 9;
				}
			}
			if (m_characterController.IsOnGround() == true) {
				if (m_jump == 9) {
					m_sprite.Init("Assets/sprite/931912.dds", 150.0f, 150.0f);
					m_sprite.SetPosition({ 0.0f,-300.0f,0.0f });
					m_sprite.Update();
					m_qteGauge = 1.0f;
					m_jump = 10;
				}
				if (m_swim == false) {
					m_eff = 0;
					m_se = 0;
				}
				m_waterJump = false;
			}
			else {
				if (m_diff.Length() >= 600.0f and m_diff2.Length() >= 600.0f and m_diff3.Length() >= 600.0f and m_diff4.Length() >= 600.0f and m_diff5.Length() >= 600.0f) {
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
			if (m_qteGauge > 0) {
				if (g_pad[0]->IsTrigger(enButtonLeft) and m_characterController.IsOnGround() == true) {
					if (m_diff.Length() <= 600.0f or m_diff2.Length() <= 600.0f or m_diff3.Length() <= 600.0f or m_diff4.Length() <= 600.0f or m_diff5.Length() <= 600.0f) {
						SoundSource* se = NewGO<SoundSource>(0);
						se->Init(4);
						se->Play(false);
						float finalSE = (pause->m_sevolume / 10.0f) * (pause->m_master / 10.0f);
						se->SetVolume(finalSE);
						m_jump = 1;
					}
				}
				if (g_pad[0]->IsTrigger(enButtonRight) and m_characterController.IsOnGround() == true) {
					if (m_diff.Length() <= 600.0f or m_diff2.Length() <= 600.0f or m_diff3.Length() <= 600.0f or m_diff4.Length() <= 600.0f or m_diff5.Length() <= 600.0f) {
						SoundSource* se = NewGO<SoundSource>(0);
						se->Init(4);
						se->Play(false);
						float finalSE = (pause->m_sevolume / 10.0f) * (pause->m_master / 10.0f);
						se->SetVolume(finalSE);
						m_jump = 2;
					}
				}
				if (g_pad[0]->IsTrigger(enButtonUp) and m_characterController.IsOnGround() == true) {
					if (m_diff.Length() <= 600.0f or m_diff2.Length() <= 600.0f or m_diff3.Length() <= 600.0f or m_diff4.Length() <= 600.0f or m_diff5.Length() <= 600.0f) {
						SoundSource* se = NewGO<SoundSource>(0);
						se->Init(4);
						se->Play(false);
						float finalSE = (pause->m_sevolume / 10.0f) * (pause->m_master / 10.0f);
						se->SetVolume(finalSE);
						m_jump = 0;
					}
				}
				if (g_pad[0]->IsTrigger(enButtonDown) and m_characterController.IsOnGround() == true) {
					if (m_diff.Length() <= 600.0f or m_diff2.Length() <= 600.0f or m_diff3.Length() <= 600.0f or m_diff4.Length() <= 600.0f or m_diff5.Length() <= 600.0f) {
						SoundSource* se = NewGO<SoundSource>(0);
						se->Init(4);
						se->Play(false);
						float finalSE = (pause->m_sevolume / 10.0f) * (pause->m_master / 10.0f);
						se->SetVolume(finalSE);
						m_jump = 3;
					}
				}
				switch (m_jump) {
				case 0:
					if (g_pad[0]->IsTrigger(enButtonUp) and m_characterController.IsOnGround() == true) {
						if (m_diff.Length() <= 600.0f or m_diff2.Length() <= 600.0f or m_diff3.Length() <= 600.0f or m_diff4.Length() <= 600.0f or m_diff5.Length() <= 600.0f) {
							m_superJump = true;
							m_velocity.y += 25.0f;
							m_sprite.Init("Assets/sprite/931911.dds", 150.0f, 200.0f);
							m_sprite.SetPosition({ 0.0f,-275.0f,0.0f });
							m_eff2 = NewGO<EffectEmitter>(0);
							m_eff2->Init(2);
							m_eff2->SetScale({ 10.0f,1.0f,10.0f });
							m_eff2->SetPosition(m_position);
							m_eff2->Play();
							SoundSource* se = NewGO<SoundSource>(0);
							se->Init(22);
							se->Play(false);
							float finalSE = (pause->m_sevolume / 10.0f) * (pause->m_master / 10.0f);
							se->SetVolume(finalSE);
							m_sprite.Update();
						}
					}
					break;
				case 1:
					if (g_pad[0]->IsTrigger(enButtonLeft) and m_characterController.IsOnGround() == true) {
						if (m_diff.Length() <= 600.0f or m_diff2.Length() <= 600.0f or m_diff3.Length() <= 600.0f or m_diff4.Length() <= 600.0f or m_diff5.Length() <= 600.0f) {
							m_superJump = true;
							m_velocity.x -= 300.0f;
							m_velocity.y += 25.0f;
							m_sprite.Init("Assets/sprite/931908.dds", 200.0f, 150.0f);
							m_sprite.SetPosition({ -25.0f,-300.0f,0.0f });
							m_eff2 = NewGO<EffectEmitter>(0);
							m_eff2->Init(2);
							m_eff2->SetScale({ 10.0f,1.0f,10.0f });
							m_eff2->SetPosition(m_position);
							m_eff2->Play();
							SoundSource* se = NewGO<SoundSource>(0);
							se->Init(22);
							se->Play(false);
							float finalSE = (pause->m_sevolume / 10.0f) * (pause->m_master / 10.0f);
							se->SetVolume(finalSE);
							m_sprite.Update();
						}
					}
					break;
				case 2:
					if (g_pad[0]->IsTrigger(enButtonRight) and m_characterController.IsOnGround() == true) {
						if (m_diff.Length() <= 600.0f or m_diff2.Length() <= 600.0f or m_diff3.Length() <= 600.0f or m_diff4.Length() <= 600.0f or m_diff5.Length() <= 600.0f) {
							m_superJump = true;
							m_velocity.y += 25.0f;
							m_velocity.x += 300.0f;
							m_sprite.Init("Assets/sprite/931902.dds", 200.0f, 150.0f);
							m_sprite.SetPosition({ 25.0f,-300.0f,0.0f });
							m_eff2 = NewGO<EffectEmitter>(0);
							m_eff2->Init(2);
							m_eff2->SetScale({ 10.0f,1.0f,10.0f });
							m_eff2->SetPosition(m_position);
							m_eff2->Play();
							SoundSource* se = NewGO<SoundSource>(0);
							se->Init(22);
							se->Play(false);
							float finalSE = (pause->m_sevolume / 10.0f) * (pause->m_master / 10.0f);
							se->SetVolume(finalSE);
							m_sprite.Update();
						}
					}
					break;
				case 3:
					if (g_pad[0]->IsTrigger(enButtonDown) and m_characterController.IsOnGround() == true) {
						if (m_diff.Length() <= 600.0f or m_diff2.Length() <= 600.0f or m_diff3.Length() <= 600.0f or m_diff4.Length() <= 600.0f or m_diff5.Length() <= 600.0f) {
							m_superJump = true;
							m_velocity.z -= 30.0f;
							m_velocity.y += 15.0f;
							m_sprite.Init("Assets/sprite/931905.dds", 150.0f, 200.0f);
							m_sprite.SetPosition({ 0.0f,-325.0f,0.0f });
							m_eff2 = NewGO<EffectEmitter>(0);
							m_eff2->Init(2);
							m_eff2->SetScale({ 10.0f,1.0f,10.0f });
							m_eff2->SetPosition(m_position);
							m_eff2->Play();
							SoundSource* se = NewGO<SoundSource>(0);
							se->Init(22);
							se->Play(false);
							float finalSE = (pause->m_sevolume / 10.0f) * (pause->m_master / 10.0f);
							se->SetVolume(finalSE);
							m_sprite.Update();
						}
					}
					break;
				}
			}
			if (m_position.y <= -60.0f) {
				if (m_swim == false) {
					m_eff = 0;
				}
				m_o2 -= 0.01f;
				m_swim = true;
				if (m_waterJump == false) {
					m_velocity.y = 0.2f;
				}
			}
			if (m_swim == true) {
				m_qteGauge = 1.0f;
				if (m_se == 0) {
					SoundSource* se = NewGO<SoundSource>(0);
					se->Init(7);
					se->Play(false);
					SoundSource* SuperSe = NewGO<SoundSource>(0);
					SuperSe->Init(18);
					SuperSe->Play(false);
					float finalSE = (pause->m_sevolume / 10.0f) * (pause->m_master / 10.0f);
					se->SetVolume(finalSE);
					SuperSe->SetVolume(finalSE);
					m_se++;
					m_effectEmitter = NewGO <EffectEmitter>(0);
					m_effectEmitter->Init(1);
					if (m_effectEmitter != nullptr) {
						m_effectEmitter->SetScale({ 20.0f,50.0f,20.0f });
						m_effectEmitter->Play();
						m_effectEmitter->SetPosition({ m_position.x,m_posy,m_position.z });
					}
					m_eff++;
				}
				if (m_se == 1) {
					if (g_pad[0]->IsTrigger(enButtonA)) {
						m_se = 0;
						if (m_effectEmitter != nullptr) {
							m_effectEmitter->Stop();
							DeleteGO(m_effectEmitter);
							m_effectEmitter = nullptr;
						}
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
				if (m_diff.Length() <= 350.0f or m_diff2.Length() <= 350.0f or m_diff3.Length() <= 350.0f or m_diff4.Length() <= 350.0f or m_diff5.Length() <= 350.0f) {
					m_hp += 0.01f;
					/*SoundSource* se = NewGO<SoundSource>(0);
					se->Init(19);
					se->Play(false);
					float finalSE = (pause->m_sevolume / 10.0f) * (pause->m_master / 10.0f);
					se->SetVolume(finalSE);*/
				}
				m_rot.SetRotationDegZ(-90.0f);
			}
			if (m_count >= 20.0f) {
				m_waterJump = true;
				m_modelRender.PlayAnimation(enAnimClip_WaterJump);
				m_se = 0;
				m_velocity.y += 25.0f;
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
			if (m_slip == true) {
				m_velocity += cameraForward * speed;
			}
			if (m_rSlip == true) {
				m_velocity.z -= 7.0f;
			}
			if (m_chase == true) {
				m_modelRender.SetAnimationSpeed(0.5f);
			}
			else {
				m_modelRender.SetAnimationSpeed(1.0f);
			}
			m_modelRender.SetPosition(m_position);
			m_modelRender.SetRotation(m_rot);
			m_position = m_characterController.Execute(m_velocity, 1.0f);
			m_modelRender.Update();
		}
		else {
			m_modelRender.Update();
		}
	}
	if (m_qteGauge > 0.5f) {
		m_qte.SetMulColor({ 0.0f,0.7f,1.0f,1.0f });
	}
	else if (m_qteGauge > 0.35f) {
		m_qte.SetMulColor({ 0.0f,1.0f,1.0f,1.0f });
	}
	else {
		m_qte.SetMulColor({ 1.0f,0.0f,0.0f,1.0f });
	}
	if (m_isEnemyNear) {
		m_qteGauge -= 0.00254f;
		if (m_qteGauge < 0.0f) {
			m_qteGauge = 0.0f;
		}
		m_gaugeCB.gaugeRate = m_qteGauge;
	}
	if (m_isEnemyNear) {
		m_vignetteAlpha = 1.0f - m_qteGauge;
	}
	else {
		m_vignetteAlpha = 0.0f;
	}
	if (m_o2StopGet == true) {
		if (m_diff.Length() <= 600.0f or m_diff2.Length() <= 600.0f or m_diff3.Length() <= 600.0f or m_diff4.Length() <= 600.0f or m_diff5.Length() <= 600.0f) {
			m_o2 -= 0.001f;
			m_o2stoptime += 1.0f / 60.0f;
			if (m_o2stoptime >= 3.0f) {
				m_o2StopGet = false;
				m_o2stoptime = 0.0f;
			}
		}
		else {
			m_o2 -= 0.002f;
			m_o2stoptime += 1.0f / 60.0f;
			if (m_o2stoptime >= 3.0f) {
				m_o2StopGet = false;
				m_o2stoptime = 0.0f;
			}
		}
	}
	if (m_superMoveGet == true) {
		m_characterController.Execute(m_velocity, 2.0f);
		m_supermovetime += 1.0f / 60.0f;
		if (m_supermovetime >= 3.0f) {
			m_superMoveGet = false;
			m_supermovetime = 0.0f;
		}
	}
	const float oneGetaSpeed = 0.1f;
	float speedDown = -0.0f - (oneGetaSpeed * m_getaCount);
	if (m_getaCount > 0) {
		m_characterController.Execute(m_velocity, speedDown);
	}
}

void Player::Render(RenderContext& rc) {
	m_modelRender.Draw(rc);
	if (m_go > 61) {
		if (m_diff.Length() <= 600.0f or m_diff2.Length() <= 600.0f or m_diff3.Length() <= 600.0f or m_diff4.Length() <= 600.0f or m_diff5.Length() <= 600.0f) {
			if (m_qteGauge > 0 and m_swim == false) {
				m_sprite.Draw(rc);
				m_qte.Draw(rc);
			    m_vignette.SetMulColor({ 0.0f,0.0f,0.0f,m_vignetteAlpha });
			}
			m_vignette.Draw(rc);
		}
		if (m_superJump == true){
			m_zone.Draw(rc);
		}
	}
}