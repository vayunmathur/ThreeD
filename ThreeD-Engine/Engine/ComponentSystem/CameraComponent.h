#pragma once
#include "Component.h"
#include "Engine/Math/Vector.h"
#include "Engine/InputSystem/InputListener.h"

class CameraComponent : public Component, public InputListener
{
public:
	CameraComponent(Scene* scene);
	~CameraComponent();
public:
	// Inherited via Component
	virtual void update() override;
	virtual void input() override;
	virtual void render() override;

	// Inherited via InputListener
	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;
	virtual void onMouseMove(const Point& mouse_pos) override;
	virtual void onLeftMouseDown(const Point& mouse_pos) override;
	virtual void onLeftMouseUp(const Point& mouse_pos) override;
	virtual void onRightMouseDown(const Point& mouse_pos) override;
	virtual void onRightMouseUp(const Point& mouse_pos) override;
public:
	mat4 getViewMatrix() { return m_mat; }
private:
	mat4 m_mat;
	float m_rot_y = 0;
	float m_rot_x = 0;
	float m_forward = 0.0f;
	float m_rightward = 0.0f;
};

