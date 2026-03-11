#pragma once
class Pengin;
class Player:public IGameObject
{
public:
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	Vector3 m_velocity = Vector3::Zero;
	Vector3 m_position;
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
	FontRender m_font;
	Pengin* m_pengin;
};

