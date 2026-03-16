#include "stdafx.h"
#include "GameOver.h"
#include "Title.h"

bool GameOver::Start() {
	return true;
}

void GameOver::Update() {
	if (g_pad[0]->IsTrigger(enButtonA)) {
		m_title = NewGO<Title>(0, "Title");
		DeleteGO(this);
	}
}

void GameOver::Render(RenderContext& rc) {

}