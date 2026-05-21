#pragma once
class Player;
class GameCamera : public IGameObject
{
public:
	bool Start();
	void Update();
	Player* m_player;
	Vector3 m_toCameraPos;//注視点から視点に向かうベクトル
	Vector3 m_currentCameraTarget;
	Vector3 m_targetToCameraPos = { 0,0,-470 };
	bool m_resetOnStart = true;
	bool m_zoom = true;
	bool m_flug = false;
	int m_i = 0;
};
