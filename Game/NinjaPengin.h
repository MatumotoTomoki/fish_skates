#pragma once
struct SCustomCb {
	float opacity;    // 透過度 (0.0 ～ 1.0)
	float isDither;   // 1.0f なら網目、0.0f なら普通 (intではなくfloatにする)
	float dummy1;     // パディング用
	float dummy2;     // パディング用
};

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
	ConstantBuffer m_cb;
	float m_opacity = 0.0f;
	bool m_stealth = true;
	int m_i = 0;

};

