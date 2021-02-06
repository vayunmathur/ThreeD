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
#include "Engine/InputSystem/InputListener.h"
#include "Engine/Math/Vector.h"
#include "Engine/ComponentSystem/Scene.h"

class AppWindow : public Window, public Scene
{
public:
	AppWindow();

	void update();

	~AppWindow();

	// Inherited via Window
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;
	virtual void onFocus() override;
	virtual void onKillFocus() override;
public:
	float getDeltaTime() { return m_delta_time; }
private:
	SwapChain* m_swap_chain;
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

