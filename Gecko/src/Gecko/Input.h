#pragma once

#include "Gecko/KeyCodes.h"
#include "Gecko/MouseCodes.h"

#include <glm/glm.hpp>

namespace Gecko {

	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);

		static bool IsMouseButtonPressed(MouseCode button);
		static glm::vec2 GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();

		static void SetCursorMode(CursorMode mode);
	};

}