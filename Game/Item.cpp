#include "stdafx.h"
#include "Item.h"

bool Item::Start()
{
	m_modelRender.Init("Assets/modelData/O2Stop(kari).tkm");
	m_modelRender.SetPosition({ 0.0f,100.0f,100.0f });
	m_modelRender.Update();
	return true;
}

void Item::Update()
{

}

void Item::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}