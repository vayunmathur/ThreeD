#include "App/AppWindow.h"
#include "Engine/ComponentSystem/Scene.h"
#include "Engine/ComponentSystem/CameraComponent.h"
#include <memory>

int main() {
	AppWindow app;
	std::shared_ptr<CameraComponent> cam = app.createComponent<CameraComponent>();
	app.getRoot()->add("camera", cam);
	if (app.init())
		while (app.isRun()) {
			app.broadcast();
		}
	return 0;
}