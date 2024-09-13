#include <Gecko.h>

class ExampleLayer : public Gecko::Layer
{
public:
	ExampleLayer();
	virtual ~ExampleLayer();

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnEvent(Gecko::Event& event) override;
	virtual void OnUpdate(Gecko::Timestep ts) override;
	virtual void OnImGuiRender() override;
private:
	unsigned int m_VertexArray;
	Gecko::Ref<Gecko::Shader> m_Shader;
	Gecko::Ref<Gecko::VertexBuffer> m_VertexBuffer;
	Gecko::Ref<Gecko::IndexBuffer> m_IndexBuffer;
	Gecko::Ref<Gecko::Texture2D> m_Texture;
};

ExampleLayer::ExampleLayer()
{
}

ExampleLayer::~ExampleLayer()
{
}

void ExampleLayer::OnAttach()
{
	glCreateVertexArrays(1, &m_VertexArray);
	glBindVertexArray(m_VertexArray);

	float vertices[3 * 12] = {
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
	};

	m_VertexBuffer.reset(Gecko::VertexBuffer::Create(vertices, sizeof(vertices)));

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	uint32_t indices[6] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	m_IndexBuffer.reset(Gecko::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

	std::string vertexSrc = R"(
			#version 330 core
			layout (location = 0) in vec3 aPos;
			layout (location = 1) in vec3 aColor;
			layout (location = 2) in vec2 aTexCoord;

			out vec3 ourColor;
			out vec2 TexCoord;

			void main()
			{
				gl_Position = vec4(aPos, 1.0);
				ourColor = aColor;
				TexCoord = vec2(aTexCoord.x, aTexCoord.y);
			}
		)";

	std::string fragmentSrc = R"(
			#version 330 core
			out vec4 FragColor;

			in vec3 ourColor;
			in vec2 TexCoord;

			// texture sampler
			uniform sampler2D texture1;

			void main()
			{
				FragColor = texture(texture1, TexCoord) * vec4(ourColor, 1.0);
				//FragColor = vec4(ourColor, 1.0);;
			}
		)";

	m_Shader = Gecko::Shader::Create("src/assets/shaders/4.1.texture.vs", "src/assets/shaders/4.1.texture.fs");
	
	m_Texture = Gecko::Texture2D::Create("src/assets/textures/wall.jpg");

	m_Shader->Bind();
	//glUniform1i(glGetUniformLocation(m_Shader->GetID(), "texture1"), 0);

	// Wireframe mode
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void ExampleLayer::OnDetach()
{
	glDeleteVertexArrays(1, &m_VertexArray);
}

void ExampleLayer::OnEvent(Gecko::Event& e)
{
	GK_TRACE("{0}", e.ToString());
}

void ExampleLayer::OnUpdate(Gecko::Timestep ts)
{
	glClearColor(0.1f, 0.1f, 0.1f, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	// Bind textures on corresponding texture units
	m_Texture->Bind(0);

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

