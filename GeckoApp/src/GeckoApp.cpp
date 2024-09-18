#include "GeckoApp.h"

#include <imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

ExampleLayer::ExampleLayer()
{
}

ExampleLayer::~ExampleLayer()
{
}

void ExampleLayer::OnAttach()
{
	m_VertexArray = Gecko::VertexArray::Create();
	//m_VertexArray->Bind();

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

	// Transform container
	// TEMP --------------------
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);

	unsigned int width = Gecko::Application::Get().GetWindow().GetWidth();
	unsigned int height = Gecko::Application::Get().GetWindow().GetHeight();
	glm::mat4 perspective = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
	m_TransformData = std::make_shared<TransformData>(model, view, perspective);
	//      --------------------

	m_Shader->Bind();
	m_Shader->SetInt("texture1", 0);
	m_Shader->SetInt("texture2", 1);

	// Wireframe mode
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void ExampleLayer::OnDetach()
{
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

	// Temp (Rotate shape)
	glm::mat4 model = glm::mat4(1.0f);
	m_TransformData->Model = glm::rotate(model, glm::radians(m_Rotate[0]), glm::vec3(1.0, 0.0, 0.0)) *
							glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotate[1]), glm::vec3(0.0, 1.0, 0.0)) *
							glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotate[2]), glm::vec3(0.0, 0.0, 1.0));

	// View
	glm::mat4 view = glm::mat4(1.0f);
	m_TransformData->View = glm::translate(view, glm::vec3(m_Translate[0], m_Translate[1], m_Translate[2]));

	// Projection
	m_TransformData->Projection = glm::perspective(glm::radians(m_Fov), m_TransformData->Width/m_TransformData->Height, m_NearPlane, m_FarPlane);

	m_Shader->SetMat4("model", m_TransformData->Model);
	m_Shader->SetMat4("view", m_TransformData->View);
	m_Shader->SetMat4("projection", m_TransformData->Projection);

	// Begin Drawing
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
	ImGui::Text("Model settings");
	ImGui::SliderFloat3("Rotate", m_Rotate, -360, 360);
	ImGui::SliderFloat3("Translate", m_Translate, -10.0f, 10.0f, "%.4f");
	ImGui::SliderFloat("FOV", &m_Fov, 0.0f, 200.0f);
	ImGui::SliderFloat("Near Plane", &m_NearPlane, 0.01f, 1.0f, "%.4f");
	ImGui::SliderFloat("Far Plane", &m_FarPlane, 100.0f, 10000.0f);
	//ImGui::SliderFloat3("Rotate", m_Rotate, -360, 360);
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

