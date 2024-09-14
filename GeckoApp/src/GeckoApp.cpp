#include <Gecko.h>

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

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
	Gecko::Ref<Gecko::Texture2D> m_TextureFace;
	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
	bool m_DisplayFace = false;
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

	m_Shader = Gecko::Shader::Create("src/assets/shaders/4.1.texture.vs", "src/assets/shaders/4.1.texture.fs");
	
	m_Texture = Gecko::Texture2D::Create("src/assets/textures/container.jpg");
	m_TextureFace = Gecko::Texture2D::Create("src/assets/textures/awesomeface.png");

	m_Shader->Bind();
	m_Shader->SetInt("texture1", 0);
	m_Shader->SetInt("texture2", 1);

	// Wireframe mode
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void ExampleLayer::OnDetach()
{
	glDeleteVertexArrays(1, &m_VertexArray);
}

void ExampleLayer::OnEvent(Gecko::Event& e)
{
	//GK_TRACE("{0}", e.ToString());
}

void ExampleLayer::OnUpdate(Gecko::Timestep ts)
{
	if (m_DisplayFace)
		m_Shader->SetFloat("mixFlag", 0.5f);
	else
		m_Shader->SetFloat("mixFlag", 0.0f);
	m_Shader->SetFloat3("color", m_SquareColor);

	glClearColor(0.1f, 0.1f, 0.1f, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	// Bind textures on corresponding texture units
	m_Texture->Bind(0);
	m_TextureFace->Bind(1);

	m_Shader->Bind();

	glBindVertexArray(m_VertexArray);
	glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
}

void ExampleLayer::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit3("Rectangle color", glm::value_ptr(m_SquareColor));
	ImGui::Checkbox("Display face", &m_DisplayFace);
	ImGui::End();
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

