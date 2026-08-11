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
class Item;
class Item2;
class Item3;
class ReversePengin;
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
		if (m_pauseBGM != nullptr)return m_pauseBGM;
		if(m_gameBGM != nullptr)return m_gameBGM;
	}
	bool m_initialized = false;
	bool m_bgmJustChanged = false;
private:
	PhysicsStaticObject m_physicsStaticObject;
	ModelRender m_modelRender;
	Vector3 m_pos;
	ModelRender m_stageRender;
	LevelRender m_stageLevelRnder;
	FontRender m_fpsFont;
	float m_deltaTime = 0.0f;
	float m_fps = 0.0f;
	long long m_prevTime = 0;
	long long m_freq = 0;
	SkyCube* m_skyCube;
	SoundSource* m_gameBGM = nullptr;
	SoundSource* m_chaseBGM = nullptr;
	SoundSource* m_menuSE = nullptr;
	SoundSource* m_selectSE = nullptr;
	SoundSource* m_pauseBGM = nullptr;
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
	Item* m_item[5];
	Item2* m_item2[5];
	Item3* m_item3[5];
	ReversePengin* m_reversePengin;
	Vector3 m_item3PosStage1[3][5] =
	{
		// パターン0：X方向
		{
			{30.0f, 100.0f, 100.0f},
			{70.0f, 100.0f, 100.0f},
			{110.0f, 100.0f, 100.0f},
			{150.0f, 100.0f, 100.0f},
			{190.0f, 100.0f, 100.0f}
		},

		// パターン1：Y方向
		{
			{30.0f, 100.0f, 100.0f},
			{30.0f, 140.0f, 100.0f},
			{30.0f, 180.0f, 100.0f},
			{30.0f, 220.0f, 100.0f},
			{30.0f, 260.0f, 100.0f}
		},

		// パターン2：Z方向
		{
			{30.0f, 100.0f, 100.0f},
			{30.0f, 100.0f, 140.0f},
			{30.0f, 100.0f, 180.0f},
			{30.0f, 100.0f, 220.0f},
			{30.0f, 100.0f, 260.0f}
		}
	};
	Vector3 m_item2PosStage1[3][5] =
	{
		// パターン0：X方向
		{
			{-30.0f, 100.0f, 100.0f},
			{-70.0f, 100.0f, 100.0f},
			{-110.0f, 100.0f, 100.0f},
			{-150.0f, 100.0f, 100.0f},
			{-190.0f, 100.0f, 100.0f}
		},

		// パターン1：Y方向
		{
			{-30.0f, 100.0f, 100.0f},
			{-30.0f, 140.0f, 100.0f},
			{-30.0f, 180.0f, 100.0f},
			{-30.0f, 220.0f, 100.0f},
			{-30.0f, 260.0f, 100.0f}
		},

		// パターン2：Z方向
		{
			{-30.0f, 100.0f, 100.0f},
			{-30.0f, 100.0f, 140.0f},
			{-30.0f, 100.0f, 180.0f},
			{-30.0f, 100.0f, 220.0f},
			{-30.0f, 100.0f, 260.0f}
		}
	};
	Vector3 m_itemPosStage1[3][5] =
	{
		// パターン0：X方向
		{
			{-30.0f, 30.0f, 100.0f},
			{-70.0f, 30.0f, 100.0f},
			{-110.0f, 30.0f, 100.0f},
			{-150.0f, 30.0f, 100.0f},
			{-190.0f, 30.0f, 100.0f}
		},

		// パターン1：Y方向
		{
			{-50.0f, 100.0f, 100.0f},
			{-50.0f, 140.0f, 100.0f},
			{-50.0f, 180.0f, 100.0f},
			{-50.0f, 220.0f, 100.0f},
			{-50.0f, 260.0f, 100.0f}
		},

		// パターン2：Z方向
		{
			{-30.0f, 30.0f, 100.0f},
			{-30.0f, 30.0f, 140.0f},
			{-30.0f, 30.0f, 180.0f},
			{-30.0f, 30.0f, 220.0f},
			{-30.0f, 30.0f, 260.0f}
		}
	};
	Vector3 m_item3PosStage2[3][5] =
	{
		// パターン0：X方向
		{
			{-30.0f, 100.0f, 100.0f},
			{-70.0f, 100.0f, 100.0f},
			{-110.0f, 100.0f, 100.0f},
			{-150.0f, 100.0f, 100.0f},
			{-190.0f, 100.0f, 100.0f}
		},

		// パターン1：Y方向
		{
			{-30.0f, 100.0f, 100.0f},
			{-30.0f, 140.0f, 100.0f},
			{-30.0f, 180.0f, 100.0f},
			{-30.0f, 220.0f, 100.0f},
			{-30.0f, 260.0f, 100.0f}
		},

		// パターン2：Z方向
		{
			{-30.0f, 100.0f, 100.0f},
			{-30.0f, 100.0f, 140.0f},
			{-30.0f, 100.0f, 180.0f},
			{-30.0f, 100.0f, 220.0f},
			{-30.0f, 100.0f, 260.0f}
		}
	};
	Vector3 m_item2PosStage2[3][5] =
	{
		// パターン0：X方向
		{
			{-30.0f, 30.0f, 100.0f},
			{-70.0f, 30.0f, 100.0f},
			{-110.0f, 30.0f, 100.0f},
			{-150.0f, 30.0f, 100.0f},
			{-190.0f, 30.0f, 100.0f}
		},

		// パターン1：Y方向
		{
			{-50.0f, 100.0f, 100.0f},
			{-50.0f, 140.0f, 100.0f},
			{-50.0f, 180.0f, 100.0f},
			{-50.0f, 220.0f, 100.0f},
			{-50.0f, 260.0f, 100.0f}
		},

		// パターン2：Z方向
		{
			{-30.0f, 30.0f, 100.0f},
			{-30.0f, 30.0f, 140.0f},
			{-30.0f, 30.0f, 180.0f},
			{-30.0f, 30.0f, 220.0f},
			{-30.0f, 30.0f, 260.0f}
		}
	};
	Vector3 m_itemPosStage2[3][5] =
	{
		// パターン0：X方向
		{
			{30.0f, 100.0f, 100.0f},
			{70.0f, 100.0f, 100.0f},
			{110.0f, 100.0f, 100.0f},
			{150.0f, 100.0f, 100.0f},
			{190.0f, 100.0f, 100.0f}
		},

		// パターン1：Y方向
		{
			{30.0f, 100.0f, 100.0f},
			{30.0f, 140.0f, 100.0f},
			{30.0f, 180.0f, 100.0f},
			{30.0f, 220.0f, 100.0f},
			{30.0f, 260.0f, 100.0f}
		},

		// パターン2：Z方向
		{
			{30.0f, 100.0f, 100.0f},
			{30.0f, 100.0f, 140.0f},
			{30.0f, 100.0f, 180.0f},
			{30.0f, 100.0f, 220.0f},
			{30.0f, 100.0f, 260.0f}
		}
	};
	// Game.h のメンバ変数定義エリア
	nsK2Engine::SPointLight* m_playerLight = nullptr; // 魚を照らすライト用ポインタ
	nsK2Engine::SPointLight* m_arrowLight = nullptr; // 矢印を照らすライト用ポインタ
	bool m_stopping = false;
	int m_skyCubeType = enSkyCubeType_Day;
	int  m_loadStep = 0;
	int m_isPause = 0;
};
