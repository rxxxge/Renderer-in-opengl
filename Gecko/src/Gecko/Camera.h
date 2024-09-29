#pragma once

#include <glm/glm.hpp>

#include "Gecko/Events/ApplicationEvent.h"

namespace Gecko {

	class Camera
	{
	public:
		Camera(float verticalFOV, float nearClip, float farClip, float width, float height);

		void OnUpdate(float ts);
		void OnEvent(Event& e);

		void OnResize(float width, float height);
	
		const glm::mat4& GetProjection() const { return m_Projection; }
		const glm::mat4& GetView() const { return m_View; }
		const glm::mat4& GetInverseProjection() const { return m_InverseProjection; }
		const glm::mat4& GetInverseView() const { return m_InverseView; }

		const glm::vec3& GetPosition() const { return m_Position; }
		const glm::vec3& GetDirection() const { return m_ForwardDirection; }

		float GetRotationSpeed();
	private:
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

		glm::vec3 m_Position{ 0.0f, 0.0f, 0.0f };
		glm::vec3 m_ForwardDirection{ 0.0f, 0.0f, 0.0f };

		glm::vec2 m_LastMousePosition{ 0.0f, 0.0f };

		float m_ViewportWidth, m_ViewportHeight;
	};

}