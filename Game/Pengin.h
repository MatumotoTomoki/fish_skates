#pragma once
class Player;
class Pengin : public IGameObject
{
public:
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	Vector3 m_pos;
private:
	
	Vector3 m_scare;
	Quaternion m_rot;
	Player* m_player;
	ModelRender m_modelRender;
	
};

