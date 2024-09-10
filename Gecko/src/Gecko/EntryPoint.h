#pragma once

#include "Log.h"

#ifdef GK_PLATFORM_WINDOWS

extern Gecko::Application* Gecko::CreateApplication(int argc, char** argv);

namespace Gecko
{

	int Main(int argc, char** argv)
	{
		Gecko::Log::Init();
		GK_CORE_INFO("Initialized logging");

		Gecko::Application* app = Gecko::CreateApplication(argc, argv);
		app->Run();
		delete app;

		return 0;
	}

}

#ifdef GK_DIST

#include <Windows.h>

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
	return Gecko::Main(__argc, __argv);
}

#else

int main(int argc, char** argv)
{
	return Gecko::Main(argc, argv);
}

#endif // GK_DIST

#endif // GK_PLATFORM_WINDOWS
