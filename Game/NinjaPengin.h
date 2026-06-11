#pragma once
class Player;
class Dummy;
class Dummy3;
class Dummy5;
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
	Vector3 m_oldPos;
	Quaternion m_rot;
	Player* m_player;
	Dummy* m_dummy;
	Dummy3* m_dummy3;
	Dummy5* m_dummy5;
	ModelRender m_modelRender;
	CharacterController m_characterController;
	bool m_change = false;
	int m_i = 0;
};
