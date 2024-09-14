#pragma once

#include "Gecko/Layer.h"

#include "Gecko/Events/ApplicationEvent.h"
#include "Gecko/Events/KeyEvent.h"
#include "Gecko/Events/MouseEvent.h"

namespace Gecko {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Event& e) override;

		void Begin();
		void End();

		inline void BlockEvents(bool block) { m_BlockEvents = block; }
	private:
		bool m_BlockEvents = true;
	};

}