#include "stdafx.h"
#include "Distance.h"
#include "Player.h"
#include "GameCamera.h"
#include "Pause.h"

namespace
{
	// 定数
	//穴との距離計算用
	const Vector3 FIRST_HOLL_POS = { 0.0f,0.0f,1300.0f };
	const Vector3 SECOND_HOLL_POS = { 2646.0f,0.0f,2500.0f };
	const Vector3 THIRD_HOLL_POS = { 4095.0f,0.0f,4600.0f };
	const Vector3 FOURTH_HOLL_POS = { 65.0f,0.0f,6500.0f };
	const Vector3 FIRST_HOLL_POS2 = { 2456.0f,0.0f,124.5f };
	const Vector3 SECOND_HOLL_POS2 = { -1201.0f,0.0f,2521.5f };
	const Vector3 THIRD_HOLL_POS2 = { -2975.0f,0.0f,3287.5f };
	const Vector3 FOURTH_HOLL_POS2 = { 1372.0f,0.0f,4839.0f };
	const float END_HOLL_POS = 99999999999.9f;
	//距離表示
	const Vector4 DISTANCE_FONT_COLOR = { 0.7f, 1.0f, 1.0f, 1.0f };
	const Vector3 DISTANCE_FONT_POS = { -745.0f, 505.0f, 0.0f };
	const Vector3 DISTANCE_FONT_TENPOS = { -765.0f, 505.0f, 0.0f };
	const Vector3 DISTANCE_FONT_HANDLETPOS = { -785.0f, 505.0f, 0.0f };
	const float MAX_DISTANCE = 999.0f;
	const float TEN_DISTANCE = 10.0f;
	const float HANDLET_DISTANCE = 10.0f;
	const float DISTANCE_FONT_SCALE = 1.0f;
}

bool Distance::Start() {
	m_pos = FIRST_HOLL_POS;
	m_player = FindGO<Player>("Player");
	auto pause = FindGO<Pause>("Pause");
	m_stage = pause->m_clearCount;
	m_model.SetPosition(m_pos);
	m_model.Update();
	return true;
}

void Distance::Update() {
	if (m_player->m_position.z >= m_pos.z) {
		m_hollState += 1;
	}
	switch (m_stage) {
	case 0:
		switch (m_hollState) {
		case 0:
			m_pos = FIRST_HOLL_POS;
			break;
		case 1:
			m_pos = SECOND_HOLL_POS;
			break;
		case 2:
			m_pos = THIRD_HOLL_POS2;
			break;
		case 3:
			m_pos = FOURTH_HOLL_POS;
			break;
		default:
			m_pos.z = END_HOLL_POS;
			break;
		}
		break;
	case 1:
		switch (m_hollState) {
		case 0:
			m_pos = FIRST_HOLL_POS2;
			break;
		case 1:
			m_pos = SECOND_HOLL_POS2;
			break;
		case 2:
			m_pos = THIRD_HOLL_POS2;
			break;
		case 3:
			m_pos = FOURTH_HOLL_POS2;
			break;
		default:
			m_pos.z = END_HOLL_POS;
			break;
		}
		break;
	}
	Vector3 center = m_pos;
	Vector3 diff = center - m_player->m_position;
	diff /= 10.0f;
	float distance = diff.Length();
	if (distance >= MAX_DISTANCE) {
		distance = MAX_DISTANCE;
	}
	wchar_t distanceText[64];
	swprintf(distanceText, 64, L"%.0f", distance);
	m_font.SetText(distanceText);
	m_font.SetColor(DISTANCE_FONT_COLOR);
	if (distance < TEN_DISTANCE) {
		m_font.SetPosition(DISTANCE_FONT_POS);
	}
	if (distance >= TEN_DISTANCE) {
		m_font.SetPosition(DISTANCE_FONT_TENPOS);
	}
	if (distance >= HANDLET_DISTANCE) {
		m_font.SetPosition(DISTANCE_FONT_HANDLETPOS);
	}
	m_font.SetScale(DISTANCE_FONT_SCALE);
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
