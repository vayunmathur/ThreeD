#pragma once
#include <map>
#include <memory>
#include "Component.h"

class Scene
{
public:
	Scene()
		: m_root(new Component(this)) {

	}
	~Scene() {}
public:
	template<typename T, typename... Args>
	std::shared_ptr<T> createComponent(Args... args) {
		return std::shared_ptr<T>(new T(args..., this));
	}
	std::shared_ptr<Component> getRoot() {
		return m_root;
	}
private:
	std::map<component_id, std::shared_ptr<Component>> m_components;
	std::shared_ptr<Component> m_root;
};

