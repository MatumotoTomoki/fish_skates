#pragma once
class Player;
class Item :public IGameObject
{
public:
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	ModelRender m_modelRender;
	PhysicsStaticObject m_physicsStaticObject;
	Player* m_player;
	Vector3 m_position;
	
};

