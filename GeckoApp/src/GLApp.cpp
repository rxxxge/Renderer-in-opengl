#include <Gecko.h>

Gecko::Application* Gecko::CreateApplication(int argc, char** argv) {
	Gecko::Application* app = new Gecko::Application();
	return app;
}