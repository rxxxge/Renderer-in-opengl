#include "GeckoApp.h"

#include <imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// TEMP
//#include <GLFW/glfw3.h>

ExampleLayer::ExampleLayer()
	: Layer("Example Layer"), m_Camera(1280.0f, 720.0f, Gecko::CameraProps::CameraProps())
{
	//m_Camera.UpdateProps(m_CameraData);
}

ExampleLayer::~ExampleLayer()
{
}

void ExampleLayer::OnAttach()
{
	m_VertexArray = Gecko::VertexArray::Create();
	//m_VertexArray->Bind();

	//float vertices[3 * 12] = {
	//	// positions          // colors           // texture coords
	//	 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
	//	 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
	//	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
	//	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
	//};

	float vertices[] = {
		// Positions          // Colors           // Texture Coords
		// Front face
		-0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f, // Bottom left
		 0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f, // Bottom right
		 0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f, // Top right
		-0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f, // Top left

		// Back face
		-0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f, // Bottom left
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f, // Bottom right
		 0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f, // Top right
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f, // Top left

		// Left face
		-0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f, // Bottom left
		-0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f, // Bottom right
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f, // Top right
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f, // Top left

		// Right face
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f, // Bottom left
		 0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f, // Bottom right
		 0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f, // Top right
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f, // Top left

		 // Top face
		 -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f, // Bottom left
		  0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f, // Bottom right
		  0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f, // Top right
		 -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f, // Top left

		 // Bottom face
		 -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f, // Bottom left
		  0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f, // Bottom right
		  0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f, // Top right
		 -0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f  // Top left
	};

	Gecko::Ref<Gecko::VertexBuffer> vertexBuffer = Gecko::VertexBuffer::Create(vertices, sizeof(vertices));
	Gecko::BufferLayout layout = {
		{ Gecko::ShaderDataType::Float3, "a_Pos" },
		{ Gecko::ShaderDataType::Float3, "a_Color" },
		{ Gecko::ShaderDataType::Float2, "a_TexCoord" }
	};

	vertexBuffer->SetLayout(layout);
	m_VertexArray->AddVertexBuffer(vertexBuffer);

	//uint32_t indices[6] = {
	//	0, 1, 3, // first triangle
	//	1, 2, 3  // second triangle
	//};

	uint32_t indices[] = {
		// Front face
		0, 1, 2,  
		2, 3, 0,

		// Back face
		4, 5, 6,  
		6, 7, 4,

		// Left face
		8, 9, 10,  
		10, 11, 8,

		// Right face
		12, 13, 14,  
		14, 15, 12,

		// Top face
		16, 17, 18,  
		18, 19, 16,

		// Bottom face
		20, 21, 22,  
		22, 23, 20
	};


	Gecko::Ref<Gecko::IndexBuffer> indexBuffer = Gecko::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
	m_VertexArray->SetIndexBuffer(indexBuffer);

	m_Shader = Gecko::Shader::Create("src/assets/shaders/4.1.texture.vs", "src/assets/shaders/4.1.texture.fs");
	
	m_Texture = Gecko::Texture2D::Create("src/assets/textures/container.jpg");
	m_TextureFace = Gecko::Texture2D::Create("src/assets/textures/awesomeface.png");

	m_Shader->Bind();
	m_Shader->SetInt("texture1", 0);
	m_Shader->SetInt("texture2", 1);
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
	// Update camera
	m_Camera.UpdateProps(m_CameraData);
	m_Camera.OnUpdate(ts);

	// Enable texture (smiley face)
	if (m_DisplayFace)
		m_Shader->SetFloat("mixFlag", m_MixValue);
	else
		m_Shader->SetFloat("mixFlag", 0.0f);
	m_Shader->SetFloat3("color", m_SquareColor);

	// Enable wireframe mode
	if (m_WireframeMode)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// View
	m_Shader->SetMat4("view", m_Camera.GetView());

	// Projection
	m_Shader->SetMat4("projection", m_Camera.GetProjection());

	// Begin Drawing
	glClearColor(0.1f, 0.1f, 0.1f, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	

	// Bind textures on corresponding texture units
	m_Texture->Bind(0);
	m_TextureFace->Bind(1);

	m_Shader->Bind();

	// TEMP ======================================= Render multiple objects
	m_VertexArray->Bind();
	glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	for (unsigned int i = 0; i < 10; i++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, cubePositions[i]);
		float angle = 20.0f * i;
		model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
		m_Shader->SetMat4("model", model);

		glDrawElements(GL_TRIANGLES, m_VertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
	// ============================================
	//glDrawElements(GL_TRIANGLES, m_VertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
}

void ExampleLayer::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::Text("Model settings");
	ImGui::ColorEdit3("Rectangle color", glm::value_ptr(m_SquareColor));
	ImGui::Checkbox("Display face", &m_DisplayFace);
	ImGui::Checkbox("Wireframe mode", &m_WireframeMode);
	ImGui::SliderFloat3("Rotate", m_Rotate, -360, 360);
	ImGui::SliderFloat3("Translate", m_Translate, -10.0f, 10.0f, "%.4f");
	ImGui::SliderFloat("Transparency", &m_MixValue, 0.0f, 1.0f);
	ImGui::Text("Camera settings");
	ImGui::SliderFloat("FOV", &m_CameraData.VerticalFOV, 0.0f, 200.0f);
	ImGui::SliderFloat("Near Plane", &m_CameraData.NearClip, 0.01f, 1.0f, "%.4f");
	ImGui::SliderFloat("Far Plane", &m_CameraData.FarClip, 100.0f, 10000.0f);
	ImGui::SliderFloat("Camera Speed", &m_CameraData.Speed, 1.0f, 100.0f);
	ImGui::SliderFloat("Camera Rotation Speed", &m_CameraData.RotationSpeed, 0.1f, 15.0f);
	//ImGui::SliderFloat3("Rotate", m_Rotate, -360, 360);
	ImGui::End();

	//m_Camera.UpdateProps(m_CameraData);
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

