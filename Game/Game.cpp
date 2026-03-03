#include "stdafx.h"
#include "Game.h"
#include "GameCamera.h"
#include "Player.h"

#include "Water.h"

bool Game::Start()
{
	



	m_stageLevelRnder.Init("Assets/modelData/Stage2.tkl", [&](LevelObjectData& odData)
		{
			if (odData.EqualObjectName(L"fish") == true)
			{
				m_modelRender.Init("Assets/modelData/fish/Fish.tkm");
				m_modelRender.SetTRS(
					odData.position,
					odData.rotation,
					odData.scale);
				g_camera3D->SetTarget(odData.position);
				auto x = odData.position;
				x.x += 100.0f;
				x.y += 100.0f;
				g_camera3D->SetPosition(x);

				return true;
			}
			if (odData.EqualObjectName(L"Stage") == true)
			{
				m_stageRender.Init("Assets/modelData/stage/Stage2.tkm");
				m_stageRender.SetTRS(
					odData.position,
					odData.rotation,
					odData.scale);
				/*float scale = 0.01f;
				m_stageRender.SetScale(scale, scale, scale);
				m_stageRender.Update();*/
				return true;
			}
			return false;
		});
	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
	
	return true;
}

void Game::Update()
{
	// g_renderingEngine->DisableRaytracing();
	m_stageRender.Update();
	m_modelRender.Update();
}

void Game::Render(RenderContext& rc)
{
	m_stageRender.Draw(rc);
	m_modelRender.Draw(rc);
	//m_stageLevelRnder.Draw(rc);
}