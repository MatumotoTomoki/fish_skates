#pragma once
class Player;
class GameCamera : public IGameObject
{
private:
	bool Start();
	void Update();
	Player* m_player;
public:
	Vector3 m_toCameraPos;//注視点から視点に向かうベクトル
	Vector3 m_currentCameraTarget;
};
