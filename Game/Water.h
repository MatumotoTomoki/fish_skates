#pragma once
class Water : public IGameObject
{
public:
	bool Start();
	void Render(RenderContext& rc);

	ModelRender m_render;
	Vector3 m_pos;
};

