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
			{1050.0f, 100.0f, 1200.0f},
			{1702.0f, 100.0f, 2140.0f},
			{1110.0f, 100.0f, 3160.0f},
			{2150.0f, 100.0f, 4170.0f},
			{3190.0f, 100.0f, 2190.0f}
		},

		// パターン1：Y方向
		{
			{1120.0f, 100.0f, 3090.0f},
			{2130.0f, 100.0f, 1200.0f},
			{2170.0f, 100.0f, 2140.0f},
			{2180.0f, 100.0f, 1280.0f},
			{2200.0f, 100.0f, 1150.0f}
		},

		// パターン2：Z方向
		{
			{1220.0f, 100.0f, 2100.0f},
			{1260.0f, 100.0f, 1400.0f},
			{3090.0f, 100.0f, 1830.0f},
			{1200.0f, 100.0f, 2220.0f},
			{2000.0f, 100.0f, 1260.0f}
		}
	};
	Vector3 m_item2PosStage1[3][5] =
	{
		// パターン0：X方向
		{
			{2090.0f, 100.0f, 1900.0f},
			{2070.0f, 100.0f, 3020.0f},
			{3110.0f, 100.0f, 2000.0f},
			{4150.0f, 100.0f, 1220.0f},
			{2190.0f, 100.0f, 1200.0f}
		},

		// パターン1：Y方向
		{
			{1956.0f, 100.0f, 1050.0f},
			{2040.0f, 100.0f, 1000.0f},
			{2002.0f, 100.0f, 1210.0f},
			{1134.0f, 100.0f, 2110.0f},
			{1289.0f, 100.0f, 2320.0f}
		},

		// パターン2：Z方向
		{
			{2330.0f, 100.0f, 1100.0f},
			{3230.0f, 100.0f, 1240.0f},
			{1830.0f, 100.0f, 2180.0f},
			{1930.0f, 100.0f, 2220.0f},
			{2120.0f, 100.0f, 1260.0f}
		}
	};
	Vector3 m_itemPosStage1[3][5] =
	{
		// パターン0：X方向
		{
			{3220.0f, 30.0f, 100.0f},
			{2370.0f, 30.0f, 100.0f},
			{4110.0f, 30.0f, 100.0f},
			{3150.0f, 30.0f, 100.0f},
			{4290.0f, 30.0f, 100.0f}
		},

		// パターン1：Y方向
		{
			{2250.0f, 100.0f, 1100.0f},
			{3950.0f, 140.0f, 1200.0f},
			{4050.0f, 180.0f, 2100.0f},
			{2250.0f, 220.0f, 2100.0f},
			{2050.0f, 260.0f, 1400.0f}
		},

		// パターン2：Z方向
		{
			{1030.0f, 30.0f, 2100.0f},
			{2030.0f, 30.0f, 1140.0f},
			{2230.0f, 30.0f, 830.0f},
			{3430.0f, 30.0f, 1220.0f},
			{2330.0f, 30.0f, 1260.0f}
		}
	};
	Vector3 m_item3PosStage2[3][5] =
	{
		// パターン0：X方向
		{
			{-1130.0f, 100.0f, 4100.0f},
			{-2370.0f, 100.0f, 2100.0f},
			{-1110.0f, 100.0f, 3100.0f},
			{-2150.0f, 100.0f, 1100.0f},
			{-4190.0f, 100.0f, 1000.0f}
		},

		// パターン1：Y方向
		{
			{-220.0f, 100.0f, 2100.0f},
			{-2330.0f, 140.0f, 2100.0f},
			{-3430.0f, 180.0f, 1200.0f},
			{-3330.0f, 220.0f, 2200.0f},
			{-3230.0f, 260.0f, 3000.0f}
		},

		// パターン2：Z方向
		{
			{-300.0f, 100.0f, 2100.0f},
			{-930.0f, 100.0f, 3140.0f},
			{-1230.0f, 100.0f, 1180.0f},
			{-900.0f, 100.0f, 3220.0f},
			{-2030.0f, 100.0f, 4260.0f}
		}
	};
	Vector3 m_item2PosStage2[3][5] =
	{
		// パターン0：X方向
		{
			{-1000.0f, 30.0f, 1900.0f},
			{-2070.0f, 30.0f, 2500.0f},
			{-1110.0f, 30.0f, 2300.0f},
			{-1250.0f, 30.0f, 1100.0f},
			{-1900.0f, 30.0f, 2100.0f}
		},

		// パターン1：Y方向
		{
			{-1250.0f, 100.0f, 1900.0f},
			{-2050.0f, 140.0f, 1100.0f},
			{-1950.0f, 180.0f, 2100.0f},
			{-1050.0f, 220.0f, 1000.0f},
			{-2150.0f, 260.0f, 2100.0f}
		},

		// パターン2：Z方向
		{
			{-1230.0f, 30.0f, 1000.0f},
			{-2130.0f, 30.0f, 2140.0f},
			{-930.0f, 30.0f, 1280.0f},
			{-430.0f, 30.0f, 2200.0f},
			{-1230.0f, 30.0f, 1260.0f}
		}
	};
	Vector3 m_itemPosStage2[3][5] =
	{
		// パターン0：X方向
		{
			{-1202.0f, 100.0f, 3100.0f},
			{-1220.0f, 100.0f, 2100.0f},
			{-2110.0f, 100.0f, 1100.0f},
			{-3150.0f, 100.0f, 900.0f},
			{-4190.0f, 100.0f, 1300.0f}
		},

		// パターン1：Y方向
		{
			{890.0f, 100.0f, 2100.0f},
			{1200.0f, 140.0f, 3000.0f},
			{230.0f, 180.0f, 2300.0f},
			{2300.0f, 220.0f, 2200.0f},
			{1130.0f, 260.0f, 3100.0f}
		},

		// パターン2：Z方向
		{
			{900.0f, 100.0f, 1100.0f},
			{1030.0f, 100.0f, 2140.0f},
			{1230.0f, 100.0f, 1980.0f},
			{1630.0f, 100.0f, 3220.0f},
			{3030.0f, 100.0f, 4260.0f}
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
