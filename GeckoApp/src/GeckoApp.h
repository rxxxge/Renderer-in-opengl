#pragma once

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
	Gecko::Ref<Gecko::VertexArray> m_VertexArray;
	Gecko::Ref<Gecko::VertexArray> m_LightVertexArray;
	Gecko::Ref<Gecko::Shader> m_Shader;
	Gecko::Ref<Gecko::Shader> m_LightShader;

	Gecko::Camera m_Camera;
	Gecko::CameraProps m_CameraData = Gecko::CameraProps::CameraProps();

	glm::vec3 m_LightColor = { 1.0f, 1.0f, 1.0f };
	glm::vec3 m_CubeColor = { 1.0f, 1.0f, 0.0f };
	bool m_WireframeMode = false;
	float m_Rotate[3] = { 0.0f };
	float m_Translate[3] = { 0.0f, 0.0f, -3.0f };
	glm::vec3 m_LightPosition = { 1.2f, 1.0f, 2.0f };
	float m_MixValue = 0.0f;
};