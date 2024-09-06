#include "GL/Application.h"
#include "GL/EntryPoint.h"

GL::Application* GL::CreateApplication(int argc, char** argv) {
	GL::Application* app = new GL::Application();
	
	return app;
}