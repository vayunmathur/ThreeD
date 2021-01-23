#pragma once
#include "Backend/Window.h"
#include "Backend/GraphicsEngine.h"
#include "Backend/SwapChain.h"
#include "Backend/DeviceContext.h"
#include "Backend/VertexBuffer.h"
class AppWindow : public Window
{
public:
	AppWindow();
	~AppWindow();

	// Inherited via Window
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;
private:
	SwapChain* m_swap_chain;
	VertexBuffer* m_vb;
};

