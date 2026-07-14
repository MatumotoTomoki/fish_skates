#include "stdafx.h"
#include "Item2.h"
#include "Player.h"

bool Item2::Start(){
	m_modelRender.Init("Assets/modelData/SuperMove.tkm");
	m_position = { 0.0f,100.0f,100.0f };
	m_modelRender.SetPosition(m_position);
	//m_player = FindGO<Player>("Player");
	m_modelRender.Update();
	return true;
}

void Item2::Update() {

}

void Item2::Render(RenderContext& rc) {
	m_modelRender.Draw(rc);
}