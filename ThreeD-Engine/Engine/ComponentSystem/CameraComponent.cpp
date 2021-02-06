#include "CameraComponent.h"
#include "Engine/InputSystem/InputSystem.h"
#include "Scene.h"
#include "App/AppWindow.h"

CameraComponent::CameraComponent(Scene* scene)
	: Component(scene)
{
	m_mat.setTranslation(vec3(0, 0, -2));
}

CameraComponent::~CameraComponent()
{
}

void CameraComponent::update()
{
	mat4 temp;

	mat4 world_cam;
	world_cam.setIdentity();
	temp.setIdentity();
	temp.setRotationX(m_rot_x);
	world_cam *= temp;
	temp.setIdentity();
	temp.setRotationY(m_rot_y);
	world_cam *= temp;


	vec3 new_pos = m_mat.getTranslation() + world_cam.getZDirection() * (m_forward * 0.3f) + world_cam.getXDirection() * (m_rightward * 0.3f);

	temp.setTranslation(new_pos);
	world_cam *= temp;
	m_mat = world_cam;
}

void CameraComponent::input()
{
}

void CameraComponent::render()
{
}

void CameraComponent::onKeyDown(int key)
{
	if (key == 'W') {
		m_forward = 1.0f;
		//m_rot_x += 0.707f * m_delta_time;
	}
	else if (key == 'S') {
		m_forward = -1.0f;
		//m_rot_x -= 0.707f * m_delta_time;
	}
	if (key == 'A') {
		m_rightward = -1.0f;
		//m_rot_y += 0.707f * m_delta_time;
	}
	else if (key == 'D') {
		m_rightward = 1.0f;
		//m_rot_y -= 0.707f * m_delta_time;
	}
}

void CameraComponent::onKeyUp(int key)
{
	m_forward = 0.0f;
	m_rightward = 0.0f;
}

void CameraComponent::onMouseMove(const Point& mouse_pos)
{
	int width = ((AppWindow*)m_scene)->getClientWindowRect().right - ((AppWindow*)m_scene)->getClientWindowRect().left;
	int height = ((AppWindow*)m_scene)->getClientWindowRect().bottom - ((AppWindow*)m_scene)->getClientWindowRect().top;
	m_rot_x += (mouse_pos.y - (height / 2.0f)) * ((AppWindow*)m_scene)->getDeltaTime() * 0.3f;
	m_rot_y += (mouse_pos.x - (width / 2.0f)) * ((AppWindow*)m_scene)->getDeltaTime() * 0.3f;

	InputSystem::get()->setCursorPosition(Point(width / 2, height / 2));
}

void CameraComponent::onLeftMouseDown(const Point& mouse_pos)
{
}

void CameraComponent::onLeftMouseUp(const Point& mouse_pos)
{
}

void CameraComponent::onRightMouseDown(const Point& mouse_pos)
{
}

void CameraComponent::onRightMouseUp(const Point& mouse_pos)
{
}
