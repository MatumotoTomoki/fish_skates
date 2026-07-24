#include "stdafx.h"
#include "Item3.h"
#include "Player.h"

bool Item3::Start() {
	m_modelRender.Init("Assets/modelData/speedDown.tkm");
	m_modelRender.SetPosition(m_position);
	m_player = FindGO<Player>("Player");
	m_modelRender.Update();
	return true;
}

void Item3::Update() {
	Vector3 diff = m_player->m_position - m_position;
	if (diff.Length() <= 80.0f) {
		m_player->m_getaCount++;
		DeleteGO(this);
	}
}

void Item3::SetPosition(const Vector3& pos)
{
	m_position = pos;
	m_modelRender.SetPosition(m_position);
	m_modelRender.Update();
}

void Item3::Render(RenderContext& rc) {
	m_modelRender.Draw(rc);
}