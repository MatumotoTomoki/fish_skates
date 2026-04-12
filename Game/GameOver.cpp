#include "stdafx.h"
#include "GameOver.h"
#include "Title.h"

bool GameOver::Start() {
	m_render.Init("Assets/sprite/gameover.dds", 1920.0f, 1080.0f);
	return true;
}

void GameOver::Update() {
	if (g_pad[0]->IsTrigger(enButtonA)) {
		NewGO<Title>(0, "Title");
		DeleteGO(this);
	}
}

void GameOver::Render(RenderContext& rc) {
	m_render.Draw(rc);
}