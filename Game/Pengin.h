#pragma once
class Player;
class Pengin : public IGameObject
{
public:
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	Vector3 m_pos;
	enum EnPenginAnimationClip {
		//enAnimClip_Walk,
		enAnimClip_Chase,
		enAnimClip_Num,
	};
	AnimationClip m_animationClips[enAnimClip_Num];
	Vector3 m_scare;
	Quaternion m_rot;
	Player* m_player;
	ModelRender m_modelRender;
	
};

