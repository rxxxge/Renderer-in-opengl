#pragma once

#include "Window.h"
#include "LayerStack.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"

#include "Timestep.h"

// TODO: ImGui Support

//#include "Gecko/Renderer/Shader.h"
//#include "Gecko/Platform/OpenGL/OpenGLBuffer.h"

namespace Gecko
{

	class Application {
	public:
		Application();
		virtual ~Application() = default;

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;

		// TEMP
		//unsigned int m_VertexArray;
		//std::unique_ptr<Shader> m_Shader; 
		//std::unique_ptr<VertexBuffer> m_VertexBuffer;
		//std::unique_ptr<IndexBuffer> m_IndexBuffer;
	private:
		static Application* s_Instance;
	};

	static Application* CreateApplication(int argc, char** argv);

}