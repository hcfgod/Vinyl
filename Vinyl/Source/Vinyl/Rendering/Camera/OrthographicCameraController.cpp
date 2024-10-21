#include "vlpch.h"
#include "OrthographicCameraController.h"

#include "Vinyl/Core/Base.h"
#include "Vinyl/Core/Input/Input.h"

namespace Vinyl
{
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool useRotation) : m_AspectRatio(aspectRatio), m_Bounds({ -m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel }), m_Camera(m_Bounds.Left, m_Bounds.Right, m_Bounds.Bottom, m_Bounds.Top), m_UseRotation(useRotation)
	{

	}

	void OrthographicCameraController::OnUpdate(TimeStep timeStep)
	{
		VL_PROFILE_FUNCTION();

		if (Input::IsKeyPressed(Vinyl::Key::W))
		{
			m_CameraPosition.y += m_CameraMoveSpeed * timeStep;
		}
		else if (Vinyl::Input::IsKeyPressed(Vinyl::Key::S))
		{
			m_CameraPosition.y -= m_CameraMoveSpeed * timeStep;
		}

		if (Input::IsKeyPressed(Vinyl::Key::A))
		{
			m_CameraPosition.x -= m_CameraMoveSpeed * timeStep;
		}
		else if (Input::IsKeyPressed(Vinyl::Key::D))
		{
			m_CameraPosition.x += m_CameraMoveSpeed * timeStep;
		}

		if (m_UseRotation)
		{
			if (Input::IsKeyPressed(Vinyl::Key::Q))
			{
				m_CameraRotation += m_CameraRotationSpeed * timeStep;
			}

			if (Input::IsKeyPressed(Vinyl::Key::E))
			{
				m_CameraRotation -= m_CameraRotationSpeed * timeStep;
			}

			m_Camera.SetRotation(m_CameraRotation);
		}

		m_Camera.SetPosition(m_CameraPosition);
	}

	void OrthographicCameraController::OnEvent(Event& event)
	{
		VL_PROFILE_FUNCTION();

		EventDispatcher eventDispatcher(event);

		eventDispatcher.Dispatch<MouseScrolledEvent>(VL_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		eventDispatcher.Dispatch<WindowResizeEvent>(VL_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	}

	void OrthographicCameraController::CalculateView()
	{
		m_Bounds = { -m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel };
		m_Camera.SetProjection(m_Bounds.Left, m_Bounds.Right, m_Bounds.Bottom, m_Bounds.Top);
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& event)
	{
		VL_PROFILE_FUNCTION();

		m_ZoomLevel -= event.GetYOffset() * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);

		CalculateView();

		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& event)
	{
		VL_PROFILE_FUNCTION();

		m_AspectRatio = (float)event.GetWidth() / (float)event.GetHeight();

		CalculateView();

		return false;
	}
}