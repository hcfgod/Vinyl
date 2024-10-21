#pragma once

#include "Vinyl/Core/Layer/Layer.h"

#include "Vinyl/Events/ApplicationEvent.h"
#include "Vinyl/Events/KeyEvent.h"
#include "Vinyl/Events/MouseEvent.h"

namespace Vinyl
{
	class VINYL_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Event& e) override;

		void Begin();
		void End();

		void SetDarkThemeColors();
		void SetBlockEvents(bool block) { m_BlockEvents = block; }
	private:
		bool m_BlockEvents = true;
	};
}