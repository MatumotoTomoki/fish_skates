#include "stdafx.h"
#include "a.h"

bool a::Start()
{
	m_stageRender.Init("Assets/modelData/stage.tkm");
	m_stageRender.SetScale(10.0f, 10.0f, 10.0f);
	m_pos.x = 0.0f;
	m_pos.y = -0.0f;
	m_stageRender.SetPosition(m_pos);
	m_stageRender.Update();
	m_physicsStaticObject.CreateFromModel(m_stageRender.GetModel(),
		m_stageRender.GetModel().GetWorldMatrix());
	return true;
}

void a::Update()
{
	// g_renderingEngine->DisableRaytracing();
	m_stageRender.Update();
}

void a::Render(RenderContext& rc)
{
	m_stageRender.Draw(rc);

}