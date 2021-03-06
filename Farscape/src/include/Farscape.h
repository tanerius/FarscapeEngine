#pragma once
#include "Versions.h"
#include "Core/Codes.h"
// Only to be used bu apps using engine
#include "Core/Log.h"

#include "Core/Timestep.h"

#include "Events/Event.h"
#include "Events/KeyEvent.h"

// Only to be used bu apps using engine
#include "Core/Application.h"
#include "Core/Input.h"
#include "Core/Layer.h"
#include "ImGui/ImGuiLayer.h"

#include "Core/Math/AABB.h"
#include "Core/Math/Ray.h"

#include "Controllers/OrthographicCameraController.h"

#include <imgui.h>

#include "Renderer/Renderer.h"
#include "Renderer/SceneRenderer.h"
#include "Renderer/RenderPass.h"
#include "Renderer/Framebuffer.h"
#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Texture.h"
#include "Renderer/Shader.h"
#include "Renderer/Mesh.h"
#include "Renderer/Camera.h"
#include "Renderer/Material.h"

#include "Scene/Entity.h"
#include "Scene/Scene.h"

// The entry point definition
//#include "Core/EntryPoint.h"