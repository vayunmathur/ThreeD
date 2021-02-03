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

class AppWindow : public Window, public InputListener
{
public:
	AppWindow();

	void updateQuadPosition();

	~AppWindow();

	// Inherited via Window
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;
	virtual void onFocus() override;
	virtual void onKillFocus() override;

	virtual void onLeftMouseDown(const Point& mouse_pos) override;
	virtual void onLeftMouseUp(const Point& mouse_pos) override;

	virtual void onRightMouseDown(const Point& mouse_pos) override;
	virtual void onRightMouseUp(const Point& mouse_pos) override;


	virtual void onKeyDown(int key);
	virtual void onKeyUp(int key);

	virtual void onMouseMove(const Point& delta_mouse_pos);
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

	float m_rot_x=0;
	float m_rot_y=0;

	float m_scale_cube = 1;
};

