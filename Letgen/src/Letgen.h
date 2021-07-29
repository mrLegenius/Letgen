#pragma once

// /////////////////////////////////////////////////////////
// -- Core -------------------------------------------------
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

#include "Letgen/Core/Application.h"
#include "Letgen/Core/Layer.h"
#include "Letgen/Core/Logger.h"

// -- GUI --------------------------------------------------

#include "Letgen/GUI/ImGuiLayer.h"

// -- Time -------------------------------------------------

#include "Letgen/Core/Timestep.h"
#include "Letgen/Core/Time.h"

// -- Input ------------------------------------------------

#include "Letgen/Input/Input.h"
#include "Letgen/Input/KeyCodes.h"
#include "Letgen/Input/MouseButtonCodes.h"

// -- ECS --------------------------------------------------

#include "Letgen/Scene/Scene.h"
#include "Letgen/Scene/Entity.h"
#include "Letgen/Scene/ScriptableEntity.h"
#include "Letgen/Scene/Component.h"

#include "Letgen/Scene/Components/CameraControllers/OrthographicCameraController.h"

// /////////////////////////////////////////////////////////
// -- Renderer ---------------------------------------------
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

#include "Letgen/Renderer/Renderer.h"
#include "Letgen/Renderer/Renderer2D.h"
#include "Letgen/Renderer/RenderCommand.h"
				 
#include "Letgen/Renderer/Buffer.h"
#include "Letgen/Renderer/VertexArray.h"
#include "Letgen/Renderer/Framebuffer.h"

#include "Letgen/Renderer/Shader.h"
#include "Letgen/Renderer/Texture.h"

#include "Letgen/Renderer/Camera/OrthographicCamera.h"

// /////////////////////////////////////////////////////////
// -- Components -------------------------------------------
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

