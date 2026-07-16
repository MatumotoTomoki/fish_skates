#pragma once
class Player;
class Item3 :public IGameObject
{
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	ModelRender m_modelRender;
	PhysicsStaticObject m_physicsStaticObject;
	Player* m_player;
	Vector3 m_position;
};

