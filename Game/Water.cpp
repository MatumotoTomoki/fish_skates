#include "stdafx.h"
#include "Water.h"

bool Water::Start() {
	m_render.Init("Assets/modelData/water.tkm");
	m_render.SetScale(9000.0f, 10.0f, 9000.0f);
	m_pos.x = 500000.0f;
	m_pos.y = -0.0f;
	m_pos.z = -50000.0f;
	m_render.SetPosition(m_pos);
	m_render.Update();
	return true;
}

void Water::Render(RenderContext& rc) {
	m_render.Draw(rc);
}