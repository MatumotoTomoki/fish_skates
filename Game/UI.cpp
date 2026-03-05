#include "stdafx.h"
#include "UI.h"

bool UI::Start()
{
	m_spriteRender.Init("Assets/sprite/distance.DDS", 500.0f, 500.0f);
	m_spriteRender.SetPosition({ -780.0f,480.0f,0.0f });
	m_spriteRender2.Init("Assets/sprite/hpGaugeFrame.DDS", 500.0f, 500.0f);
	m_spriteRender2.SetPosition({ 780.0f,480.0f,0.0f });
	m_spriteRender3.Init("Assets/sprite/hpGauge.DDS", 340.0f, 25.0f);
	m_spriteRender3.SetPosition({ 780.0f,485.0f,0.0f });
	m_spriteRender4.Init("Assets/sprite/O2GaugeFrame.DDS", 500.0f, 500.0f);
	m_spriteRender4.SetPosition({ 780.0f,380.0f,0.0f });
	m_spriteRender5.Init("Assets/sprite/O2Gauge.dds", 340.0f, 25.0f);
	m_spriteRender5.SetPosition({ 780.0f,385.0f,0.0f });
	
	return true;
}

void UI::Update()
{
	m_o2 += 0.001f;
	m_spriteRender5.SetPivot({ 1.0,0.53f });
	m_spriteRender5.SetScale({ m_o2,1.0f,0.0f });
	m_spriteRender5.SetPosition({ 600.0f,385.0f,0.0f });
	if (m_o2 > -0.1f) {
		m_o2 = -0.1f;
	}

	m_spriteRender3.SetPivot({ 1.0,0.53f });
	m_spriteRender3.SetScale({ -1.05f,1.0f,0.0f });
	m_spriteRender3.SetPosition({ 600.0f,485.0f,0.0f });

	m_spriteRender.Update();
	m_spriteRender2.Update();
	m_spriteRender3.Update();
	m_spriteRender4.Update();
	m_spriteRender5.Update();
}

void UI::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
	m_spriteRender3.Draw(rc);
	m_spriteRender2.Draw(rc);
	m_spriteRender5.Draw(rc);
	m_spriteRender4.Draw(rc);
}
