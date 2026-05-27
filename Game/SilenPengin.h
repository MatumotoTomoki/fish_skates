#pragma once
class Pause;
class Player;
class SilenPengin : public IGameObject
{
public:
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	void SetSEVolume(float vol) {
		if (m_se) {
			m_se->SetVolume(vol);
		}
	}
	Vector3 m_pos;
	enum EnPenginAnimationClip {
		enAnimClip_Chase,
		enAnimClip_Num,
	};
	AnimationClip m_animationClips[enAnimClip_Num];
	Vector3 m_scare;
	Quaternion m_rot;
	Player* m_player;
	ModelRender m_modelRender;
	SoundSource* m_se;
	Pause* m_pause;
	float m_coolTime = 100.0f;
	int m_silen = 0;
};
