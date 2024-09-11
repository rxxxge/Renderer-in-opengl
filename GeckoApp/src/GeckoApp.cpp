#include <Gecko.h>

using namespace Gecko;

class ExampleLayer : public Gecko::Layer
{
public:
	ExampleLayer();
	virtual ~ExampleLayer();

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnEvent(Event& event) override;
	virtual void OnUpdate(Timestep ts) override;
	virtual void OnImGuiRender() override;
private:
	unsigned int m_VertexArray;
	std::unique_ptr<Shader> m_Shader;
	std::unique_ptr<VertexBuffer> m_VertexBuffer;
	std::unique_ptr<IndexBuffer> m_IndexBuffer;
};

ExampleLayer::ExampleLayer()
{
}

ExampleLayer::~ExampleLayer()
{
}

void ExampleLayer::OnAttach()
{
	glGenVertexArrays(1, &m_VertexArray);
	glBindVertexArray(m_VertexArray);

	float vertices[3 * 6] = {
		// positions         // colors
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
	};

	m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	uint32_t indices[6] = {
		0, 1, 2,
		4, 2, 3
	};

	m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

	std::string vertexSrc = R"(
			#version 330 core

			layout (location = 0) in vec3 a_Position;
			layout (location = 1) in vec3 a_Color;		// The color variable has attribute position 1

			out	vec3 outputColor; // output color to the fragment shader

			void main()
			{
				gl_Position = vec4(a_Position.x, a_Position.y, a_Position.z, 1.0);
				outputColor = a_Color;	
			}
		)";

	std::string fragmentSrc = R"(
			#version 330 core
			
			out vec4 FragColor;
			in vec3 outputColor;

			void main()
			{
				FragColor = vec4(outputColor, 1.0);
			}
		)";

	m_Shader.reset(new Shader(vertexSrc, fragmentSrc));

	// Wireframe mode
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void ExampleLayer::OnDetach()
{
	glDeleteVertexArrays(1, &m_VertexArray);
}

void ExampleLayer::OnEvent(Event& e)
{
	GK_TRACE("{0}", e.ToString());
}

void ExampleLayer::OnUpdate(Timestep ts)
{
	glClearColor(0.1f, 0.1f, 0.1f, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	m_Shader->Bind();

	glBindVertexArray(m_VertexArray);
	glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
}

void ExampleLayer::OnImGuiRender()
{
}


class ExampleApp : public Gecko::Application
{
public:
	ExampleApp()
	{
		PushLayer(new ExampleLayer());
	}
};

Gecko::Application* Gecko::CreateApplication(int argc, char** argv) {
	//Gecko::Application* app = new Gecko::Application();
	//return app;

	return new ExampleApp();
}

