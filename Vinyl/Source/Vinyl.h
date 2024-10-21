#pragma once

// For use Vinyl applications

#include "Vinyl/Core/Application.h"
#include "Vinyl/Core/Layer/Layer.h"
#include "Vinyl/ImGui/ImGuiLayer.h"
#include "Vinyl/Core/Log.h"

#include "Vinyl/Core/TimeStep.h"

#include "Vinyl/Core/Input/Input.h"
#include "Vinyl/Core/Input/KeyCodes.h"
#include "Vinyl/Core/Input/MouseCodes.h"

#include "Vinyl/Rendering/Renderer/Renderer.h"
#include "Vinyl/Rendering/Renderer/Renderer2D.h"
#include "Vinyl/Rendering/Renderer/RenderCommand.h"

#include "Vinyl/Rendering/Buffer.h"
#include "Vinyl/Rendering/Shader.h"
#include "Vinyl/Rendering/Framebuffer.h"
#include "Vinyl/Rendering/VertexArray.h"
#include "Vinyl/Rendering/Texture.h"
#include "Vinyl/Rendering/SubTexture2D.h"

#include "Vinyl/Rendering/Camera/OrthographicCamera.h"
#include "Vinyl/Rendering/Camera/OrthographicCameraController.h"

#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>