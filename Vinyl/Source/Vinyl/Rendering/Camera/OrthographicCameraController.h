#pragma once

#include "Vinyl/Rendering/Camera/OrthographicCamera.h"
#include "Vinyl/Core/TimeStep.h"

#include "Vinyl/Events/ApplicationEvent.h"
#include "Vinyl/Events/MouseEvent.h"

namespace Vinyl
{
	struct OrthographicCameraBounds
	{
		float Left, Right;
		float Bottom, Top;

		float GetWidth() { return Right - Left; }
		float GetHeight() { return Top - Bottom; }
	};

	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool useRotation = false);

		void OnUpdate(TimeStep timeStep);
		void OnEvent(Event& event);
		void OnResize(float width, float height);

		inline OrthographicCamera& GetCamera() { return m_Camera; }
		inline const OrthographicCamera& GetCamera() const { return m_Camera; }

		inline void SetZoomLevel(float level) 
		{
			m_ZoomLevel = level; 
			CalculateView();
		}

		inline float GetZoomLevel() { return m_ZoomLevel; }

		const OrthographicCameraBounds& GetBounds() const { return m_Bounds; }
	private:
		void CalculateView();

		bool OnMouseScrolled(MouseScrolledEvent& event);
		bool OnWindowResized(WindowResizeEvent& event);
	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrthographicCameraBounds m_Bounds;
		OrthographicCamera m_Camera;

		bool m_UseRotation = false;

		glm::vec3 m_CameraPosition{ 0.0f };
		float m_CameraRotation = 0.0f;

		float m_CameraMoveSpeed = 3.5f;
		float m_CameraRotationSpeed = 180.0f;
	};
}