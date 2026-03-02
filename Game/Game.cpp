#include "stdafx.h"
#include "Game.h"
#include "GameCamera.h"
#include "Player.h"
#include "a.h"
#include "Water.h"

bool Game::Start()
{
	NewGO<Player>(0, "Player");
	NewGO<GameCamera>(0, "GameCamera");
	NewGO<Water>(0, "Water");
	m_a = NewGO<a>(0, "wserdtfyguh");
	a * k = NewGO<a>(0, "wserdtfyguh");
	k->m_pos = { 0.0f,0.0f,1300.0f };
	Water* water2 = NewGO<Water>(0, "Water");
	water2->m_pos = { 0.0f,0.0f,1200.0f };

	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
	
	return true;
}

void Game::Update()
{
	// g_renderingEngine->DisableRaytracing();
	//m_stageRender.Update();
}

void Game::Render(RenderContext& rc)
{
	//m_stageRender.Draw(rc);
	
}