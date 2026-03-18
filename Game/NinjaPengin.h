#pragma once
struct SCustomCb {
	float opacity;    // 0.0f ～ 1.0f
	float isDither;   // 1.0f 固定（網目にするフラグ）
	float padding[2]; // 16バイト境界合わせ
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

