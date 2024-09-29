#pragma once

#include <glm/glm.hpp>

#include "Gecko/Events/ApplicationEvent.h"

namespace Gecko {

	struct CameraProps
	{
		float VerticalFOV;
		float NearClip;
		float FarClip;

		float Speed = 5.0f;
		float RotationSpeed = 0.6f;

		CameraProps(float verticalFOV = 45.0f, float nearClip = 0.1f, float farClip = 100.0f)
			: VerticalFOV(verticalFOV), NearClip(nearClip), FarClip(farClip)
		{
		}
	};

	class Camera
	{
	public:
		Camera(float width, float height, CameraProps& props);

		void OnUpdate(float ts);
		void OnEvent(Event& e);

		void OnResize(float width, float height);
		void UpdateProps(CameraProps& props);
	
		const glm::mat4& GetProjection() const { return m_Projection; }
		const glm::mat4& GetView() const { return m_View; }
		const glm::mat4& GetInverseProjection() const { return m_InverseProjection; }
		const glm::mat4& GetInverseView() const { return m_InverseView; }

		const glm::vec3& GetPosition() const { return m_Position; }
		const glm::vec3& GetDirection() const { return m_ForwardDirection; }
	private:
		bool HandleInput(glm::vec2 delta, float ts);
		void RecalculateProjection();
		void RecalculateView();
		bool OnWindowResized(WindowResizeEvent& e);
	private:
		glm::mat4 m_Projection{ 1.0f };
		glm::mat4 m_View{ 1.0f };
		glm::mat4 m_InverseProjection{ 1.0f };
		glm::mat4 m_InverseView{ 1.0f };

		float m_VerticalFOV;
		float m_NearClip;
		float m_FarClip;
		
		float m_Speed;
		float m_RotationSpeed;

		float m_ViewportWidth, m_ViewportHeight;

		glm::vec3 m_Position{ 0.0f, 0.0f, 0.0f };
		glm::vec3 m_ForwardDirection{ 0.0f, 0.0f, 0.0f };
		glm::vec2 m_LastMousePosition{ 0.0f, 0.0f };
	};

}