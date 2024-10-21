#pragma once

#include "Vinyl/Core/Base.h"
#include "Vinyl/Events/Event.h"

#include "Vinyl/Core/TimeStep.h"

namespace Vinyl
{
	class VINYL_API Layer
	{
	public:
		Layer(const std::string& debugName = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(TimeStep timestep) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};
}