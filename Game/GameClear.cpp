#include "stdafx.h"
#include "GameClear.h"
#include "Title.h"
#include "Pause.h"

bool GameClear::Start(){
	m_spriteRender.Init("Assets/sprite/GameClear.DDS", 1920.0f, 1080.0f);
	auto pause = FindGO<Pause>("Pause");
	m_bgm = NewGO<SoundSource>(0);
	m_bgm->Init(9);
	m_bgm->Play(false);
	float finalSE = (pause->m_volume / 10.0f) * (pause->m_master / 10.0f);
	m_bgm->SetVolume(finalSE);
	return true;
}

void GameClear::Update(){
	if (g_pad[0]->IsTrigger(enButtonA)){
		DeleteGO(m_bgm);
		NewGO<Title>(0, "Title");
		DeleteGO(this);
	}
}

void GameClear::Render(RenderContext& rc){
	m_spriteRender.Draw(rc);
}

