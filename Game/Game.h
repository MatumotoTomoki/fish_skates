#pragma once

#include "Level3DRender/LevelRender.h"

class GameCamera;
class Player;
class UI;
class Pengin;
class NinjaPengin;
class SilenPengin;
class Water;
class Dummy;
class Dummy3;
class Dummy5;
class GameOver;
class Pause;
class Game : public IGameObject
{
public:
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	void SetBGMVolume(float vol) {
		if (m_gameBGM) {
			m_gameBGM->SetVolume(vol);
		}
	}

private:
	PhysicsStaticObject m_physicsStaticObject;
	ModelRender m_modelRender;
	Vector3 m_pos;
	ModelRender m_stageRender;
	LevelRender m_stageLevelRnder;
	SkyCube* m_skyCube;
	SoundSource* m_gameBGM = nullptr;
	Player* m_player;
	GameCamera* m_gameCamera;
	GameOver* m_gameOver;
	UI* m_ui;
	Water* m_water;
	Pengin* m_pengin;
	NinjaPengin* m_ninjaPengin;
	SilenPengin* m_silenPengin;
	Dummy* m_dummy;
	Dummy3* m_dummy3;
	Dummy5* m_dummy5;
	Pause* m_pause;
	bool m_isBgmOn = true;
	bool m_isSeOn = true;

	int m_skyCubeType = enSkyCubeType_Day;
	
};

