#pragma once
class Player;
class Item :public IGameObject
{
public:
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	void SetPosition(const Vector3& pos);
	void Floating();
	ModelRender m_modelRender;
	PhysicsStaticObject m_physicsStaticObject;
	Player* m_player;
	Vector3 m_position;
	float m_oldYPos;
	float m_timer = 0.0f;
};
