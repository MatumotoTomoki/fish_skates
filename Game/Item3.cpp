#include "stdafx.h"
#include "Item3.h"
#include "Player.h"
#include "Pause.h"

bool Item3::Start() {
	m_modelRender.Init("Assets/modelData/speedDown.tkm");
	m_modelRender.SetPosition(m_position);
	m_player = FindGO<Player>("Player");
	m_modelRender.Update();
	return true;
}

void Item3::Update() {
	auto pause = FindGO<Pause>("Pause");
	Vector3 diff = m_player->m_position - m_position;
	if (diff.Length() <= 80.0f) {
		m_player->m_getaCount++;
		SoundSource* se = NewGO<SoundSource>(0);
		se->Init(22);
		se->Play(false);
		float finalSE = (pause->m_sevolume / 10.0f) * (pause->m_master / 10.0f);
		se->SetVolume(finalSE);
		m_effectEmitter = NewGO <EffectEmitter>(0);
		m_effectEmitter->Init(4);
		m_effectEmitter->SetScale({ 10.0f,10.0f,10.0f });
		m_effectEmitter->Play();
		DeleteGO(this);
	}
	if (m_effectEmitter != nullptr) {
		m_effectEmitter->SetPosition({ m_player->m_position });
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