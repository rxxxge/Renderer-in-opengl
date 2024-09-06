#pragma once

namespace GL 
{

	class Application {
	public:
		Application();
		~Application();

		void Run();
	private:
		bool m_Running;
	};

	static Application* CreateApplication(int argc, char** argv);
}