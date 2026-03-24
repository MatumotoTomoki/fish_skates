#pragma once
class Player;
class Dummy;
class NinjaPengin:public IGameObject
{
public:
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	Vector3 m_pos;
	enum EnPenginAnimationClip {
		enAnimClip_Walk,
		enAnimClip_Chase,
		enAnimClip_Num,
	};
	AnimationClip m_animationClips[enAnimClip_Num];
	Vector3 m_scare;
	Quaternion m_rot;
	Player* m_player;
	Dummy* m_dummy;
	ModelRender m_modelRender;
	CharacterController m_characterController;
	bool m_stealth = true;
	int m_i = 0;

};

