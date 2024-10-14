#pragma once

#include "Vinyl/Layer/Layer.h"

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
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event& e) override;

		void Begin();
		void End();

		void SetDarkThemeColors();
	private:
		bool m_BlockEvents = true;
	};
}