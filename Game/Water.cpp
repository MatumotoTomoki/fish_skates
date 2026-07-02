#include "stdafx.h"
#include "Water.h"

bool Water::Start() {
	m_render.Init("Assets/modelData/water.tkm");
	ModelInitData initData;
	m_cb.Init(sizeof(WaterConstantBuffer));
	initData.m_tkmFilePath = "Assets/modelData/water.tkm";
	initData.m_fxFilePath = "Assets/shader/preProcess/water.fx"; // ★ここで新しいシェーダーを指定
	initData.m_expandConstantBuffer = &m_cbData;
	initData.m_expandConstantBufferSize = sizeof(m_cbData);
	m_render.InitForwardRendering(initData); // 専用の初期化関数を呼ぶ
	m_render.SetScale(900.0f, 10.0f, 900.0f);
	m_pos.x = 5.0f;
	m_pos.y = -30.0f;
	m_pos.z = 5.0f;
	m_render.SetPosition(m_pos);
	m_render.Update();
	return true;
}

void Water::Update() {
	OutputDebugStringA("Water Update\n");
	float deltaTime = 1.0f / 60.0f; // とりあえず固定値で動かしてみる
	m_time += deltaTime;
	// VRAMへ送信
	m_cbData.time = m_time;
	m_cb.CopyToVRAM(m_cbData);
	m_render.Update();
}

void Water::Render(RenderContext& rc) {
	rc.SetConstantBuffer(1, m_cb);
	m_render.Draw(rc);
}
