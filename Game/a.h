#pragma once
class a : public IGameObject
{
public:
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	Vector3 m_pos;
private:
	PhysicsStaticObject m_physicsStaticObject;
	ModelRender m_modelRender;
	
	ModelRender m_stageRender;
	SkyCube* m_skyCube;
	int m_skyCubeType = enSkyCubeType_Day;
};

