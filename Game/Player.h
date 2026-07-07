#pragma once
class Pengin;
class NinjaPengin;
class SilenPengin;
class Dummy5;
class Item;
class Player :public IGameObject
{
public:
	struct CustomBuffer
	{
		float opacity;
		float isDither;
		float smoothness; // ★シェーダーの並び順と完全に合わせる
		float padding;
	};
	~Player();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	Vector3 m_velocity = Vector3::Zero;
	Vector3 m_position;
	Vector3 m_diff;
	Vector3 m_diff2;
	Vector3 m_diff3;
	Vector3 m_diff4;
	Quaternion m_rot;
	ModelRender m_modelRender;
	CharacterController m_characterController;
	Vector3 GetPosition() const { return m_position; }
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
	bool m_start = false;
	bool m_chase = false;
	float m_hp = -1.05f;
	float m_o2 = -1.05f;
	float m_count = 0.0f;
	float m_posy = -100.0f;
	float m_vignetteAlpha = 0.0f;
	int m_i = 0;
	int m_se = 0;
	int m_eff = 0;
	int m_efk = 0;
	int m_jump = 0;
	int m_go = 0;
	int m_qteUI = 0;
	SpriteRender m_sprite;
	SpriteRender m_qte;
	SpriteRender m_vignette;
	SpriteRender m_zone;
	FontRender m_font;
	Pengin* m_pengin = nullptr;
	NinjaPengin* m_ninjaPengin = nullptr;
	SilenPengin* m_silenPengin = nullptr;
	Dummy5* m_dummy5 = nullptr;
	EffectEmitter* m_effectEmitter = nullptr;
	EffectEmitter* m_eff2 = nullptr;
	Item* m_item = nullptr;
	float m_qteGauge = 1.0f;
	float m_o2stoptime = 0.0f;
	bool m_isEnemyNear = false;
	bool m_slip = false;
	bool O2StopGet = false;
	bool m_o2stoplose = false;
	struct GaugeCB
	{
		float gaugeRate;
		float pad[3];
	};
	GaugeCB m_gaugeCB;
};
