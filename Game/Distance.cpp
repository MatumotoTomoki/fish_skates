#include "stdafx.h"
#include "Distance.h"
#include "Player.h"

bool Distance::Start() {
	m_pos = { 0.0f,0.0f,999.0f };
	m_player = FindGO<Player>("Player");
	m_model.Init("Assets/modelData/distance.tkm");
	m_model.SetPosition(m_pos);
	m_model.Update();
	return true;
}

void Distance::Update() {
	if (m_player->m_position.z >= m_pos.z) {
		m_hollState += 1;
	}
	switch (m_hollState)
	{
	case 0:
		m_pos = { 0.0f,0.0f,1300.0f };
		break;
	case 1:
		m_pos = { 2646.0f,0.0f,1900.0f };
		break;
	case 2:
		m_pos = { 4095.0f,0.0f,4600.0f };
		break;
	case 3:
		m_pos = { 65.0f,0.0f,6500.0f };
		break;
	/*case 4:
		m_pos = { 0.0f,0.0f,5000.0f };
		break;*/
	default:
		DeleteGO(this);
		break;
	}
	Vector3 center = m_pos;
	wchar_t distanceText[64];
	Vector3 diff = center - m_player->m_position;
	float distance = diff.Length();
	if (distance >= 999.0f) {
		distance = 999.0f;
	}
	swprintf(distanceText, 64, L"%.0f", distance);
	m_font.SetText(distanceText);
	m_font.SetColor(0.0f, 1.0f, 1.0f, 1.0f);
	if (distance < 10.0f) {
		m_font.SetPosition(-830.0f, 510.0f, 0.0f);
	}
	if (distance >= 10.0f) {
		m_font.SetPosition(-850.0f, 510.0f, 0.0f);
	}
	if (distance >= 100.0f) {
		m_font.SetPosition(-870.0f, 510.0f, 0.0f);
	}
	m_font.SetScale(1.0f);
	m_model.SetPosition(m_pos);
	m_model.Update();
}

void Distance::Render(RenderContext& rc) {
	m_font.Draw(rc);
	//m_model.Draw(rc);
}