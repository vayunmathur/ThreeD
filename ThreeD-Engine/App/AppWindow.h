#pragma once
#include "Engine/Window/Window.h"
#include "Engine/GraphicsEngine/GraphicsEngine.h"
#include "Engine/GraphicsEngine/SwapChain.h"
#include "Engine/GraphicsEngine/DeviceContext.h"
#include "Engine/GraphicsEngine/VertexBuffer.h"
#include "Engine/GraphicsEngine/IndexBuffer.h"
#include "Engine/GraphicsEngine/ConstantBuffer.h"
#include "Engine/GraphicsEngine/VertexShader.h"
#include "Engine/GraphicsEngine/PixelShader.h"

class AppWindow : public Window
{
public:
	AppWindow();

	void updateQuadPosition();

	~AppWindow();

	// Inherited via Window
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;
private:
	SwapChain* m_swap_chain;
	VertexBuffer* m_vb;
	IndexBuffer* m_ib;
	VertexShader* m_vs;
	PixelShader* m_ps;
	ConstantBuffer* m_cb;
private:
	float m_old_delta;
	float m_new_delta;
	float m_delta_time;

	float m_delta_pos;
	float m_delta_scale;
};

