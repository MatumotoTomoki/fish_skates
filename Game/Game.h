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
class Game : public IGameObject
{
public:
	bool Start();
	void Update();
	void Render(RenderContext& rc);

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
	UI* m_ui;
	Water* m_water;
	Pengin* m_pengin;
	NinjaPengin* m_ninjaPengin;
	SilenPengin* m_silenPengin;
	Dummy* m_dummy;
	int m_skyCubeType = enSkyCubeType_Day;
	
};

