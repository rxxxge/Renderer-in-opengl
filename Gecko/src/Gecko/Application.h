#pragma once

#include "Window.h"

#include "Gecko/Renderer/Shader.h"

namespace Gecko
{

	class Application {
	public:
		Application();
		~Application();

		void Run();
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;

		unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;
		std::unique_ptr<Shader> m_Shader;
	};

	static Application* CreateApplication(int argc, char** argv);

}