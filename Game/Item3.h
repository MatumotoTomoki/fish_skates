#pragma once
class Player;
class Item3 :public IGameObject
{
public:
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	void SetPosition(const Vector3& pos);
	void Move();
	ModelRender m_modelRender;
	PhysicsStaticObject m_physicsStaticObject;
	Player* m_player;
	Vector3 m_position;
	Quaternion rot;
	EffectEmitter* m_effectEmitter = nullptr;
	int m_itemDeleteCount = 0;
	int m_effectCount = 0;
	bool m_deleteSwitch = false;
};

