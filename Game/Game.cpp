#include "stdafx.h"
#include "Game.h"
#include "GameCamera.h"
#include "Player.h"
#include"sound/SoundEngine.h"
#include "Water.h"
#include "UI.h"
#include "Pengin.h"

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
				
				m_player = NewGO<Player>(0, "Player");
				m_gameCamera = NewGO<GameCamera>(0, "GameCamera");
				m_ui = NewGO<UI>(0, "ui");
				m_pengin = NewGO<Pengin>(0, "Pengin");
				g_soundEngine->ResistWaveFileBank(0, "Assets/Sound/fish.wav");
				m_gameBGM = NewGO<SoundSource>(0);
				m_gameBGM->Init(0);
				m_gameBGM->Play(true);
				m_skyCube = NewGO<SkyCube>(0);
				Water* water = NewGO<Water>(0);

				return true;
			}
			if (odData.EqualObjectName(L"Stage") == true)
			{
				m_stageRender.Init("Assets/modelData/tairiku3.tkm");
				m_stageRender.SetTRS(
					odData.position,
					odData.rotation,
					odData.scale);
				m_stageRender.SetPosition(0.0f, -475.0f, 0.0f);
				m_stageRender.SetScale(100.0f, 100.0f, 100.0f);
				m_stageRender.Update();
				m_physicsStaticObject.CreateFromModel(m_stageRender.GetModel(),
					m_stageRender.GetModel().GetWorldMatrix());
				return true;
			}

			
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