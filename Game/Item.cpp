#include "stdafx.h"
#include "Item.h"
#include "Player.h"

bool Item::Start() {
	m_modelRender.Init("Assets/modelData/O2Stop(kari).tkm");
	m_position = { 760.0f,30.0f,3310.0f };
	m_modelRender.SetPosition(m_position);
	m_player = FindGO<Player>("Player");
	m_modelRender.Update();
	return true;
}

void Item::Update() {
	Vector3 diff = m_player->m_position - m_position;
	if (diff.Length() <= 80.0f) {
		m_player->m_o2StopGet = true;
		DeleteGO(this);
	}
}

void Item::Render(RenderContext& rc) {
	m_modelRender.Draw(rc);
}