#pragma once
class Player;
class GameCamera : public IGameObject
{
	bool Start();
	void Update();
	Player* m_player;
	Vector3 m_toCameraPos;//注視点から視点に向かうベクトル
	Vector3 m_currentCameraTarget;
	int m_i = 0;
};
