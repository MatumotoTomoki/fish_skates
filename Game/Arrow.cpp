#include "stdafx.h"
#include "Arrow.h"
#include "Player.h"
#include "Distance.h"
bool Arrow::Start() {
	m_modelRender.Init("Assets/modelData/Arrow.tkm");
	m_modelRender.SetShadowCasterFlag(false);
	m_player = FindGO<Player>("Player");
	m_distance = FindGO<Distance>("Distance");
	m_position = { m_player->m_position.x,10.0f,m_player->m_position.z };
	m_modelRender.SetPosition(m_position);
	Quaternion rot;
	rot.SetRotationDegX(90.0f);
	m_modelRender.SetRotation(rot);
	m_modelRender.SetScale(0.7f, 0.7f, 0.7f);
	m_modelRender.Update();
	return true;
}

void Arrow::Update() {
	m_position = { m_player->m_position.x,m_player->m_position.y,m_player->m_position.z };
	m_position.y += 100.0f;
	m_modelRender.SetPosition(m_position);
	Vector3 toArrow = m_position - m_distance->m_pos;
	toArrow.Normalize();
	float toAlloedir = atan2f(toArrow.x, toArrow.z);
	m_rot.SetRotationY(toAlloedir);
	m_modelRender.SetRotation(m_rot);
	m_modelRender.Update();
}

void Arrow::Render(RenderContext& rc) {
	m_modelRender.Draw(rc);
}