#pragma once
class Item :public IGameObject
{
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	ModelRender m_modelRender;
	PhysicsStaticObject m_physicsStaticObject;
};

