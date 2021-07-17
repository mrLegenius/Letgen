#pragma once

// /////////////////////////////////////////////////////////
// -- Core -------------------------------------------------
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

#include "Core/Application.h"
#include "Core/Layer.h"
#include "Core/Logger.h"

#include "Core/Timestep.h"
#include "Core/Time.h"

#include "Core/Input.h"
#include "Core/KeyCodes.h"
#include "Core/MouseButtonCodes.h"

#include "Core/GUI/ImGuiLayer.h"

// /////////////////////////////////////////////////////////
// -- Renderer ---------------------------------------------
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

#include "Core/Renderer/Renderer.h"
#include "Core/Renderer/RenderCommand.h"

#include "Core/Renderer/Buffer.h"
#include "Core/Renderer/VertexArray.h"

#include "Core/Renderer/Shader.h"
#include "Core/Renderer/Texture.h"

#include "Core/Renderer/Camera/OrthographicCamera.h"

// /////////////////////////////////////////////////////////
// -- Components -------------------------------------------
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

#include "Core/Transform.h"
#include "Core/Components/CameraControllers/OrthographicCameraController.h"

// /////////////////////////////////////////////////////////
// -- Entry Point ------------------------------------------
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

#include "Core/EntryPoint.h"