#pragma once

// /////////////////////////////////////////////////////////
// -- Core -------------------------------------------------
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

#include "Letgen/Core/Application.h"
#include "Letgen/Core/Layer.h"
#include "Letgen/Core/Logger.h"

#include "Letgen/Core/Timestep.h"
#include "Letgen/Core/Time.h"

#include "Letgen/Input/Input.h"
#include "Letgen/Input/KeyCodes.h"
#include "Letgen/Input/MouseButtonCodes.h"

#include "Letgen/GUI/ImGuiLayer.h"

// /////////////////////////////////////////////////////////
// -- Renderer ---------------------------------------------
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

#include "Letgen/Renderer/Renderer.h"
#include "Letgen/Renderer/RenderCommand.h"
				 
#include "Letgen/Renderer/Buffer.h"
#include "Letgen/Renderer/VertexArray.h"

#include "Letgen/Renderer/Shader.h"
#include "Letgen/Renderer/Texture.h"

#include "Letgen/Renderer/Camera/OrthographicCamera.h"

// /////////////////////////////////////////////////////////
// -- Components -------------------------------------------
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

#include "Letgen/Components/Transform.h"
#include "Letgen/Components/CameraControllers/OrthographicCameraController.h"

// /////////////////////////////////////////////////////////
// -- Entry Point ------------------------------------------
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

#include "Letgen/Core/EntryPoint.h"