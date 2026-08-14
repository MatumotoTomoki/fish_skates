#include "stdafx.h"
#include "Item.h"
#include "Player.h"

bool Item::Start() {
	m_modelRender.Init("Assets/modelData/O2Stop(kari).tkm");
	m_modelRender.SetPosition(m_position);
	m_player = FindGO<Player>("Player");
	m_oldYPos = m_position.y;
	m_modelRender.Update();
	return true;
}

void Item::Update() {
	Floating();
	Vector3 diff = m_player->m_position - m_position;
	if (diff.Length() <= 80.0f) {
		m_player->m_o2StopGet = true;
		m_player->m_supermovetime = 0.0f;
		DeleteGO(this);
	}
	m_modelRender.SetPosition(m_position);
	m_modelRender.Update();
}

void Item::SetPosition(const Vector3& pos) {
	m_position = pos;
	m_modelRender.SetPosition(m_position);
	m_modelRender.Update();
}

void Item::Floating() {
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

void Item::Render(RenderContext& rc) {
	m_modelRender.Draw(rc);
}