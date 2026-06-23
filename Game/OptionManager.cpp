#include "stdafx.h"
#include "OptionManager.h"
#include "Title.h"
#include "Pause.h"
#include "Game.h"

void OptionManager::Update() {
	auto title = FindGO<Title>("Title");
	if (title != nullptr) {
		m_bgmVol = title->m_bgmVol;
		m_seVol = title->m_seVol;
		m_masVol = title->m_masVol;
		if (title->m_optionMode) {
			m_camera = title->m_specialCamera;
		}
		if (m_volCount >= 1) {
			title->m_specialCamera = m_camera;
			title->m_bgmVol = m_bgmMenuVol;
			title->m_seVol = m_seMenuVol;
			title->m_masVol = m_masMenuVol;
			m_volCount = 0;
		}
	}
	auto pause = FindGO<Pause>("Pause");
	if (pause != nullptr) {
		auto game = FindGO<Game>("Game");
		if (game != nullptr) {
			m_volCount++;
		}
		if (m_volCount == 0) {
			pause->m_volume = m_bgmVol;
			pause->m_sevolume = m_seVol;
			pause->m_master = m_masVol;
		}
		m_bgmMenuVol = pause->m_volume;
		m_seMenuVol = pause->m_sevolume;
		m_masMenuVol = pause->m_master;
	}
}