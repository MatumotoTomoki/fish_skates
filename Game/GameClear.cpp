#include "stdafx.h"
#include "GameClear.h"
#include "Title.h"

bool GameClear::Start(){
	m_spriteRender.Init("Assets/sprite/GameClear.DDS", 1920.0f, 1080.0f);
	return true;
}

void GameClear::Update(){
	if (g_pad[0]->IsTrigger(enButtonA)){
		NewGO<Title>(0, "Title");
		DeleteGO(this);
	}
}

void GameClear::Render(RenderContext& rc){
	m_spriteRender.Draw(rc);
}

