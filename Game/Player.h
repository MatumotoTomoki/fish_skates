#pragma once
class Pengin;
class NinjaPengin;
class SilenPengin;
class Player:public IGameObject
{
public:
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	Vector3 m_velocity = Vector3::Zero;
	Vector3 m_position;
	Vector3 m_diff;
	Vector3 m_diff2;
	Vector3 m_diff3;
	Quaternion m_rot;
	ModelRender m_modelRender;
	CharacterController m_characterController;
	enum EnAnimationClip {
		enAnimClip_Idle,
		enAnimClip_Jump,
		enAnimClip_Swim,
		enAnimClip_WaterJump,
		enAnimClip_Num,
	};
	AnimationClip m_animationClips[enAnimClip_Num];
	bool m_swim = false;
	bool m_waterJump = false;
	bool m_superJump = false;
	float m_hp = -1.05f;
	float m_o2 = -1.05f;
	int m_i = 0;
	SpriteRender m_sprite;
	Pengin* m_pengin;
	NinjaPengin* m_ninjaPengin;
	SilenPengin* m_silenPengin;
};

