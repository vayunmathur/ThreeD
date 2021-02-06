#pragma once
#include <map>
#include <memory>
#include <string>

class Scene;

using component_id = unsigned long long;

class Component
{
public:
	Component(Scene* scene) 
		: m_scene(scene) {

	}
	~Component() {

	}
public:
	virtual void update() {}
	virtual void input() {}
	virtual void render() {}
public:
	void updateAll() {
		update();
		for (auto&&[name, comp] : children) {
			comp->updateAll();
		}
	}
	void inputAll() {
		input();
		for (auto&& [name, comp] : children) {
			comp->inputAll();
		}
	}
	void renderAll() {
		render();
		for (auto&& [name, comp] : children) {
			comp->renderAll();
		}
	}
public:
	inline component_id getID() { return m_id; }
	void add(std::string str, std::shared_ptr<Component> component) {
		children[str] = component;
	}
	template<typename T>
	std::shared_ptr<T> get(std::string str) {
		return std::dynamic_pointer_cast<T>(children[str]);
	}
	void remove(std::string str) {
		children.erase(str);
	}
protected:
	Scene* m_scene;
private:
	component_id m_id;
	std::string str;
	std::map<std::string, std::shared_ptr<Component>> children;
};

