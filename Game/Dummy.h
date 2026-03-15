#pragma once
class Player;
class NinjaPengin;
class Dummy : public IGameObject
{
public:
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	Vector3 m_pos;
	Vector3 m_oldPos;
	enum EnPenginAnimationClip {
		enAnimClip_Walk,
		enAnimClip_Chase,
		enAnimClip_Num,
	};
	AnimationClip m_animationClips[enAnimClip_Num];
	Vector3 m_scare;
	Quaternion m_rot;
	Player* m_player;
	NinjaPengin* m_ninjaPengin;
	ModelRender m_modelRender;
	CharacterController m_characterController;
	bool m_change = false;

};

