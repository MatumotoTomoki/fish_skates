#pragma once
class Player;
class Distance;
class Arrow : public IGameObject
{
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	ModelRender m_modelRender;
	Vector3 m_position;
	Player* m_player;
	Distance* m_distance;
	Quaternion m_rot;
};

