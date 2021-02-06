#include "AppWindow.h"
#include <Windows.h>
#include "Engine/Math/Vector.h"
#include "Engine/InputSystem/InputSystem.h"
#include "Engine/ComponentSystem/CameraComponent.h"
#include "Engine/ComponentSystem/EntityComponent.h"

__declspec(align(16))
struct constant
{
	mat4 m_transform;
	mat4 m_view;
	mat4 m_projection;
	unsigned int m_time;
};

AppWindow::AppWindow()
{
}

void AppWindow::update()
{
	constant cc;
	cc.m_time = GetTickCount64();

	cc.m_transform = getRoot()->get<EntityComponent>("box")->getTransformationMatrix();

	mat4 world_cam = getRoot()->get<CameraComponent>("camera")->getViewMatrix();

	world_cam.inverse();



	cc.m_view = world_cam;

	int width = this->getClientWindowRect().right - this->getClientWindowRect().left;
	int height = this->getClientWindowRect().bottom - this->getClientWindowRect().top;

	cc.m_projection.setPerspectiveFovLH(1.57f, (float)width / (float)height, 0.1f, 100.0f);


	m_cb->update(GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext(), &cc);
}

AppWindow::~AppWindow()
{
}

void AppWindow::onCreate()
{
	Window::onCreate();

	InputSystem::get()->addListener(getRoot()->get<CameraComponent>("camera").get());
	InputSystem::get()->showCursor(false);

	GraphicsEngine::get()->init();
	RECT rc = this->getClientWindowRect();
	m_swap_chain = GraphicsEngine::get()->getRenderSystem()->createSwapChain(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	vertex vertex_list[] =
	{
		{vec3(-0.5f,-0.5f,-0.5f),	vec3(1,0,0),	vec3(0.2f,0,0)},
		{vec3(-0.5f, 0.5f,-0.5f),	vec3(1,1,0),	vec3(0.2f,0.2f,0)},
		{vec3(0.5f, 0.5f,-0.5f),	vec3(1,1,0),	vec3(0.2f,0.2f,0)},
		{vec3(0.5f, -0.5f,-0.5f),	vec3(1,0,0),	vec3(0.2f,0,0)},

		{vec3(0.5f,-0.5f,0.5f),		vec3(0,1,0),	vec3(0,0.2f,0)},
		{vec3(0.5f, 0.5f,0.5f),		vec3(0,1,1),	vec3(0,0.2f,0.2f)},
		{vec3(-0.5f, 0.5f,0.5f),	vec3(0,1,1),	vec3(0,0.2f,0.2f)},
		{vec3(-0.5f, -0.5f,0.5f),	vec3(0,1,0),	vec3(0,0.2f,0)}
	};

	unsigned int index_list[] =
	{
		0, 1, 2,
		2, 3, 0,
		4, 5, 6,
		6, 7, 4,
		1, 6, 5,
		5, 2, 1,
		7, 0, 3,
		3, 4, 7,
		3, 2, 5,
		5, 4, 3,
		7, 6, 1,
		1, 0, 7
	};

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	GraphicsEngine::get()->getRenderSystem()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = GraphicsEngine::get()->getRenderSystem()->createVertexShader(shader_byte_code, size_shader);
	getRoot()->add("box", createComponent<EntityComponent>(vertex_list, ARRAYSIZE(vertex_list), index_list, ARRAYSIZE(index_list), shader_byte_code, size_shader));
	GraphicsEngine::get()->getRenderSystem()->releaseCompiledShader();


	GraphicsEngine::get()->getRenderSystem()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->getRenderSystem()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->getRenderSystem()->releaseCompiledShader();

	constant cc;
	cc.m_time = 0;

	m_cb = GraphicsEngine::get()->getRenderSystem()->createConstantBuffer(&cc, sizeof(constant));
}

void AppWindow::onUpdate()
{
	Window::onUpdate();

	InputSystem::get()->update();

	getRoot()->updateAll();

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->clearRenderTargetColor(m_swap_chain, 0, 0.3f, 0.4f, 1);

	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	update();

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);


	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setPixelShader(m_ps);

	getRoot()->renderAll();

	m_swap_chain->present(false);

	m_old_delta = m_new_delta;
	m_new_delta = ::GetTickCount64();

	m_delta_time = m_old_delta?(m_new_delta - m_old_delta)/1000.0f:0;
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	GraphicsEngine::get()->getRenderSystem()->release();
}

void AppWindow::onFocus()
{
	InputSystem::get()->addListener(getRoot()->get<CameraComponent>("camera").get());
}

void AppWindow::onKillFocus()
{
	InputSystem::get()->removeListener(getRoot()->get<CameraComponent>("camera").get());
}