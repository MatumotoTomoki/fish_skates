#include "stdafx.h"
#include "Water.h"

bool Water::Start() {
	m_render.Init("Assets/modelData/water.tkm");
	m_render.SetScale(10.0f, 10.0f, 10.0f);
	m_pos.x = 0.0f;
	m_pos.y = -0.0f;
	m_render.SetPosition(m_pos);
	m_render.Update();
	return true;
}

void Water::Render(RenderContext& rc) {
	m_render.Draw(rc);
}