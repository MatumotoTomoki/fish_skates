#include "stdafx.h"
#include "Item2.h"
#include "Player.h"
#include "Pause.h"

bool Item2::Start() {
	m_modelRender.Init("Assets/modelData/SuperMove.tkm");
	m_modelRender.SetPosition(m_position);
	m_player = FindGO<Player>("Player");
	m_modelRender.Update();
	return true;
}

void Item2::Update() {
	auto pause = FindGO<Pause>("Pause");
	Vector3 diff = m_player->m_position - m_position;
	if (diff.Length() <= 80.0f) {
		m_player->m_superMoveGet = true;
		m_player->m_supermovetime = 0.0f;
		SoundSource* se = NewGO<SoundSource>(0);
		se->Init(22);
		se->Play(false);
		float finalSE = (pause->m_sevolume / 10.0f) * (pause->m_master / 10.0f);
		se->SetVolume(finalSE);
		DeleteGO(this);
	}
}

void Item2::SetPosition(const Vector3& pos) {
	m_position = pos;
	m_modelRender.SetPosition(m_position);
	m_modelRender.Update();
}

void Item2::Render(RenderContext& rc) {
	m_modelRender.Draw(rc);
}