#pragma once
class OptionManager : public IGameObject
{
public:
	void Update();
	int m_bgmVol;
	int m_seVol;
	int m_masVol;
	int m_volCount = 0;
	int m_bgmMenuVol;
	int m_seMenuVol;
	int m_masMenuVol;
	int m_difficult;
	bool m_camera;
};
