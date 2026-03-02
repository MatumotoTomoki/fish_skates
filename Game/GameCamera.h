#pragma once
class Player;
class Game;
class GameCamera : public IGameObject
{
private:
	bool Start();
	void Update();




public:
	Vector3 m_toCameraPos;//注視点から視点に向かうベクトル
	Vector3 m_currentCameraTarget;




private:
	Player* m_player;
	Game* m_game;
	int m_count = 0;
	bool m_cameraUp = false;




public:

};
