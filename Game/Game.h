#pragma once

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
class Pause;
class Distance;
class Arrow;
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
	static void Preload();
	static void PreEnd(bool flug) {
		flug = true;
	}
	SoundSource* GetCurrentBGM() {
		if (m_chaseBGM != nullptr) return m_chaseBGM;
		return m_gameBGM;
	}
	bool m_initialized = false;
	bool m_bgmJustChanged = false;
private:
	PhysicsStaticObject m_physicsStaticObject;
	ModelRender m_modelRender;
	Vector3 m_pos;
	ModelRender m_stageRender;
	LevelRender m_stageLevelRnder;
	SkyCube* m_skyCube;
	SoundSource* m_gameBGM = nullptr;
	SoundSource* m_chaseBGM = nullptr;
	SoundSource* m_menuSE = nullptr;
	SoundSource* m_selectSE = nullptr;
	Player* m_player;
	GameCamera* m_gameCamera;
	UI* m_ui;
	Water* m_water;
	Pengin* m_pengin;
	NinjaPengin* m_ninjaPengin;
	SilenPengin* m_silenPengin;
	Dummy* m_dummy;
	Dummy3* m_dummy3;
	Dummy5* m_dummy5;
	Pause* m_pause;
	Distance* m_distance;
	Arrow* m_arrow;
	bool m_stop = false;
	int m_skyCubeType = enSkyCubeType_Day;
	int  m_loadStep = 0;
};
