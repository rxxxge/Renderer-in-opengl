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
	Gecko::Ref<Gecko::Shader> m_Shader;
	Gecko::Ref<Gecko::VertexArray> m_VertexArray;

	Gecko::Ref<Gecko::Texture2D> m_Texture;
	Gecko::Ref<Gecko::Texture2D> m_TextureFace;
	// Temp
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
	m_VertexArray = Gecko::VertexArray::Create();
	m_VertexArray->Bind();

	float vertices[3 * 12] = {
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
	};

	Gecko::Ref<Gecko::VertexBuffer> vertexBuffer = Gecko::VertexBuffer::Create(vertices, sizeof(vertices));
	Gecko::BufferLayout layout = {
		{ Gecko::ShaderDataType::Float3, "a_Pos" },
		{ Gecko::ShaderDataType::Float3, "a_Color" },
		{ Gecko::ShaderDataType::Float2, "a_TexCoord" }
	};

	vertexBuffer->SetLayout(layout);
	m_VertexArray->AddVertexBuffer(vertexBuffer);

	uint32_t indices[6] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	Gecko::Ref<Gecko::IndexBuffer> indexBuffer = Gecko::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
	m_VertexArray->SetIndexBuffer(indexBuffer);

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
	/*glDeleteVertexArrays(1, &m_VertexArray);*/
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

	m_VertexArray->Bind();
	glDrawElements(GL_TRIANGLES, m_VertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
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

