#include "gkpch.h"
#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#include "Input.h"

namespace Gecko {

	Camera::Camera(float verticalFOV = 45.0f, float nearClip = 0.1f, float farClip = 100.0f, float width = 1280.0f, float height = 720.0f)
		: m_VerticalFOV(verticalFOV), m_NearClip(nearClip), m_FarClip(farClip), m_ViewportWidth(width), m_ViewportHeight(height)
	{
		m_ForwardDirection = glm::vec3(0, 0, -1);
		m_Position = glm::vec3(0, 0, 3);

		RecalculateView();
		RecalculateProjection();
	}

	void Camera::OnUpdate(float ts)
	{
		glm::vec2 mousePos = Input::GetMousePosition();
		glm::vec2 delta = (mousePos - m_LastMousePosition) * 0.002f;
		m_LastMousePosition = mousePos;

		if (!Input::IsMouseButtonPressed(Mouse::ButtonRight))
		{
			Input::SetCursorMode(CursorMode::Normal);
			return;
		}

		Input::SetCursorMode(CursorMode::Locked);

		bool moved = false;

		constexpr glm::vec3 upDirection(0.0f, 1.0f, 0.0f);
		glm::vec3 rightDirection = glm::cross(m_ForwardDirection, upDirection);

		float speed = 10.0f;

		if (Input::IsKeyPressed(Key::W))
		{
			m_Position += m_ForwardDirection * speed * ts;
			moved = true;
		}
		else if (Input::IsKeyPressed(Key::S))
		{
			m_Position -= m_ForwardDirection * speed * ts;
			moved = true;
		}

		if (Input::IsKeyPressed(Key::A))
		{
			m_Position -= rightDirection * speed * ts;
			moved = true;
		}
		else if (Input::IsKeyPressed(Key::D))
		{
			m_Position += rightDirection * speed * ts;
		}
		// Maybe will remove
		if (Input::IsKeyPressed(Key::Q))
		{
			m_Position -= upDirection * speed * ts;
			moved = true;
		}
		else if (Input::IsKeyPressed(Key::E))
		{
			m_Position += upDirection * speed * ts;
			moved = true;
		}

		// Rotation
		if (delta.x != 0.0f || delta.y != 0.0f)
		{
			float pitchDelta = delta.y * GetRotationSpeed();
			float yawDelta = delta.x * GetRotationSpeed();

			glm::quat q = glm::normalize(glm::cross(glm::angleAxis(-pitchDelta, rightDirection),
				glm::angleAxis(-yawDelta, glm::vec3(0.0f, 1.0f, 0.0f))));
			m_ForwardDirection = glm::rotate(q, m_ForwardDirection);

			moved = true;
		}

		if (moved)
		{
			RecalculateView();
			RecalculateProjection();
		}
	}

	void Camera::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowResizeEvent>(GK_BIND_EVENT_FN(Camera::OnWindowResized));
	}

	void Camera::OnResize(float width, float height)
	{
		if (width == m_ViewportWidth && height == m_ViewportHeight)
			return;

		m_ViewportWidth = width;
		m_ViewportHeight = height;

		RecalculateProjection();
	}

	float Camera::GetRotationSpeed()
	{
		return 0.6f;
	}

	void Camera::RecalculateProjection()
	{
		m_Projection = glm::perspectiveFov(glm::radians(m_VerticalFOV), m_ViewportWidth, m_ViewportHeight, m_NearClip, m_FarClip);
		m_InverseProjection = glm::inverse(m_Projection);
	}

	void Camera::RecalculateView()
	{
		m_View = glm::lookAt(m_Position, m_Position + m_ForwardDirection, glm::vec3(0, 1, 0));
		m_InverseView = glm::inverse(m_View);
	}

	bool Camera::OnWindowResized(WindowResizeEvent& e)
	{
		OnResize((float)e.GetWidth(), (float)e.GetHeight());
		return false;
	}

}