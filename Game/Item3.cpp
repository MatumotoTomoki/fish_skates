#include "stdafx.h"
#include "Item3.h"
#include "Player.h"
#include "Pause.h"

bool Item3::Start() {
	m_modelRender.Init("Assets/modelData/speedDown.tkm");
	m_modelRender.SetPosition(m_position);
	m_player = FindGO<Player>("Player");
	m_oldYPos = m_position.y;
	m_modelRender.Update();
	return true;
}

void Item3::Update() {
	auto pause = FindGO<Pause>("Pause");
	Move();
	Floating();
	Vector3 diff = m_player->m_position - m_position;
	if (diff.Length() <= 80.0f) {
		m_player->m_getaCount++;
		//エフェクトを追従させるために削除せずに見えない位置(地下深く)まで飛ばす
		m_position.y = -9999999999999999999.0f;
		SoundSource* se = NewGO<SoundSource>(0);
		se->Init(22);
		se->Play(false);
		float finalSE = (pause->m_sevolume / 10.0f) * (pause->m_master / 10.0f);
		se->SetVolume(finalSE);
		//エフェクトが出る回数を一回に制限
		if (m_effectCount == 0) {
			m_effectEmitter = NewGO <EffectEmitter>(0);
			m_effectEmitter->Init(4);
			m_effectEmitter->SetScale({ 10.0f,10.0f,10.0f });
			m_effectEmitter->Play();
		}
		m_deleteSwitch = true;
	}
	if (m_effectEmitter != nullptr) {
		m_effectEmitter->SetPosition(m_player->m_position);
	}
	//エフェクトが消えるくらいの時間でアイテムを消す
	if (m_deleteSwitch == true) {
		m_itemDeleteCount++;
	}
	if (m_itemDeleteCount >= 155) {
		DeleteGO(this);
	}
	m_modelRender.SetPosition(m_position);
	m_modelRender.Update();
}

void Item3::Move() {
	rot.AddRotationDegY(2.0f);
	m_modelRender.SetRotation(rot);
}

void Item3::Floating() {
	// 経過時間を進める（値が大きいほど浮遊のスピードが速くなります）
	// GameTime等のデルタタイムを掛けるとフレームレートに依存しなくなりますが、
	// ここでは分かりやすく一定数ずつ加算する例にしています
	m_timer += 0.05f;
	// sin関数を使って -1.0f から 1.0f の間で滑らかに往復させる
	// sin波を使うことで、上下の端で自然に減速・加速（イージング）します
	float floatAmount = sinf(m_timer);
	// 基準の高さ（m_oldYPos）から上下に 10.0f の幅で動かす
	m_position.y = m_oldYPos + floatAmount * 10.0f;
}

void Item3::SetPosition(const Vector3& pos) {
	m_position = pos;
	m_modelRender.SetPosition(m_position);
	m_modelRender.Update();
}

void Item3::Render(RenderContext& rc) {
	m_modelRender.Draw(rc);
}