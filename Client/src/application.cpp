#include "application.h"

Application* application = NULL;

Application::Application() : log("client"), config("client") {
	if (!log.initialized()) {
		throw "Log could not be initialized";
	}

	if (!config.initialized()) {
		throw "Config could not be loaded";
	}

	config.save();
}

Application::~Application() {
	config.save();
}

void Application::update() {

}