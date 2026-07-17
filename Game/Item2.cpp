#include "stdafx.h"
#include "Item2.h"
#include "Player.h"

bool Item2::Start() {
	m_modelRender.Init("Assets/modelData/SuperMove.tkm");
	m_position = { 0.0f,100.0f,100.0f };
	m_modelRender.SetPosition(m_position);
	m_player = FindGO<Player>("Player");
	m_modelRender.Update();
	return true;
}

void Item2::Update() {
	Vector3 diff = m_player->m_position - m_position;
	if (diff.Length() <= 80.0f) {
		m_player->m_superMoveGet = true;
		DeleteGO(this);
	}
}

void Item2::Render(RenderContext& rc) {
	m_modelRender.Draw(rc);
}