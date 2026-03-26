#pragma once
class Player;
class NinjaPengin;
class Dummy3;
class Dummy5 : public IGameObject
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
	Dummy3* m_dummy3;
	ModelRender m_modelRender;
	CharacterController m_characterController;
	EffectEmitter* m_effectEmitter = nullptr;			//エフェクト。
	bool m_change = false;
	int m_i = 0;
	int m_effect = 0;
};

