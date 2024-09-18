#pragma once

#include <Gecko.h>

struct TransformData
{
	float Width, Height;
	glm::mat4 Model;
	glm::mat4 View;
	glm::mat4 Projection;
	
	TransformData(glm::mat4 model, glm::mat4 view, glm::mat4 projection)
	{
		unsigned int width = Gecko::Application::Get().GetWindow().GetWidth();
		unsigned int height = Gecko::Application::Get().GetWindow().GetHeight();

		Width = (float)width;
		Height = (float)height;

		Model = model;
		View = view;
		Projection = projection;
	}
};

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
	float m_Rotate[3] = { 0.0f };
	float m_Translate[3] = { 0.0f, 0.0f, -3.0f };
	float m_Fov = 45.0f;
	float m_NearPlane = 0.1f;
	float m_FarPlane = 100.0f;
	Gecko::Ref<TransformData> m_TransformData;
};