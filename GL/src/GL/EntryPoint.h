#pragma once

#ifdef X_PLATFORM_WINDOWS

extern GL::Application* GL::CreateApplication(int argc, char** argv);
bool g_ApplicationRunning = true;

namespace GL
{

	int Main(int argc, char** argv)
	{
		while (g_ApplicationRunning)
		{
			GL::Application* app = GL::CreateApplication(argc, argv);
			app->Run();
			delete app;
		}

		return 0;
	}

}

#ifdef X_DIST

#include <Windows.h>

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
	return Vulkan::Main(__argc, __argv);
}

#else

int main(int argc, char** argv)
{
	return GL::Main(argc, argv);
}

#endif // X_DIST

#endif // X_PLATFORM_WINDOWS
