#pragma once

#include "Window.h"

#include "Gecko/Renderer/Shader.h"
#include "Gecko/Platform/OpenGL/OpenGLBuffer.h"

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

		unsigned int m_VertexArray;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
	};

	static Application* CreateApplication(int argc, char** argv);

}