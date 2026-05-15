#include "stdafx.h"
#include "Distance.h"
#include "Player.h"

bool Distance::Start() {
	m_pos = { 0.0f,0.0f,999.0f };
	m_player = FindGO<Player>("Player");
	m_model.SetPosition(m_pos);
	m_model.Update();
	return true;
}

void Distance::Update() {
	if (m_player->m_position.z >= m_pos.z) {
		m_hollState += 1;
	}
	switch (m_hollState) {
	case 0:
		m_pos = { 0.0f,0.0f,1300.0f };
		break;
	case 1:
		m_pos = { 2646.0f,0.0f,2500.0f };
		break;
	case 2:
		m_pos = { 4095.0f,0.0f,4600.0f };
		break;
	case 3:
		m_pos = { 65.0f,0.0f,6500.0f };
		break;
	default:
		m_pos.z = 99999999999.9f;
		break;
	}
	Vector3 center = m_pos;
	Vector3 diff = center - m_player->m_position;
	diff /= 10.0f;
	float distance = diff.Length();
	if (distance >= 999.0f) {
		distance = 999.0f;
	}
	wchar_t distanceText[64];
	swprintf(distanceText, 64, L"%.0f", distance);
	m_font.SetText(distanceText);
	m_font.SetColor(0.7f, 1.0f, 1.0f, 1.0f);
	if (distance < 10.0f) {
		m_font.SetPosition(-745.0f, 505.0f, 0.0f);
	}
	if (distance >= 10.0f) {
		m_font.SetPosition(-765.0f, 505.0f, 0.0f);
	}
	if (distance >= 100.0f) {
		m_font.SetPosition(-785.0f, 505.0f, 0.0f);
	}
	m_font.SetScale(1.0f);
	m_model.SetPosition(m_pos);
	m_model.Update();
}

void Distance::Render(RenderContext& rc) {
	if (m_player->m_start == true) {
		if (m_hollState < 4) {
			m_font.Draw(rc);
		}
	}
}
