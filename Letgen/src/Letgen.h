#pragma once


#pragma region ***Client side includes***

#include "Core/Application.h"
#include "Core/Layer.h"
#include "Core/Logger.h"
#include "Core/GUI/ImGuiLayer.h"

#include "Core/Events/Event.h"
#include "Core/Events/ApplicationEvent.h"
#include "Core/Events/KeyEvent.h"
#include "Core/Events/MouseEvent.h"

#include "Core/Input.h"
#include "Core/KeyCodes.h"
#include "Core/MouseButton.h"

#pragma region ***Renderer***
#include "Core/Renderer/Renderer.h"
#include "Core/Renderer/RenderCommand.h"

#include "Core/Renderer/Buffer.h"
#include "Core/Renderer/Shader.h"
#include "Core/Renderer/VertexArray.h"

#include "Core/Renderer/Camera/OrthographicCamera.h"

#pragma endregion 
#pragma endregion 


#pragma region ***EntryPoint***
#include "Core/EntryPoint.h"
#pragma endregion 