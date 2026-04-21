#pragma once
class Player;
class Distance : public IGameObject
{
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	Player* m_player;
	FontRender m_font;
	ModelRender m_model;
	int m_hollState = 0;
public:
	Vector3 m_pos;
};

