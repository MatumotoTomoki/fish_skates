#pragma once
class Water : public IGameObject
{
	struct WaterConstantBuffer {
		float opacity;
		float isDither;
		float smoothness;
		float time; // ★ここに追加
	};
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	ModelRender m_render;
	Vector3 m_pos;
	PhysicsStaticObject m_physicsStaticObject;
	ConstantBuffer m_cb; // 定数バッファ用クラス
	WaterConstantBuffer m_cbData; // 送信データ保持用
	float m_time = 0.0f;
};
