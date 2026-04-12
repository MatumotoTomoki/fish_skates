#pragma once
class Player;
class Distance : public IGameObject
{
public:
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	Vector3 m_pos;
	Player* m_player;
	FontRender m_font;
	ModelRender m_model;
	int m_hollState = 0;
};

