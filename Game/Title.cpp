#include "stdafx.h"
#include "Title.h"
#include "Game.h"

bool Title::Start() {
	m_render.Init("Assets/sprite/title.dds", 1920.0f, 1080.0f);
	return true;
}

void Title::Update() {
	if (g_pad[0]->IsTrigger(enButtonA)) {
		m_flug = true;
		m_font.SetText(L"3");
		m_game->Preload();
	}
	if (m_flug == true) {
		m_count -= 0.015f;
	}
	if (m_count <= 2.0f) {
		m_font.SetText(L"2");
	}
	if (m_count <= 1.0f) {
		m_font.SetText(L"1");
	}
	if (m_count <= 0.0f) {
		m_font.SetText(L"GO!");
	}
	if (m_count <= -1.0f) {
		NewGO<Game>(0, "Game");
		DeleteGO(this);
	}
}

void Title::Render(RenderContext& rc) {
	if (m_flug == false) {
		m_render.Draw(rc);
	}
	m_font.Draw(rc);
}