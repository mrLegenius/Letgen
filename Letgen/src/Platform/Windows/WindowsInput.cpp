#include "pch.h"

#include <GLFW/glfw3.h>

#include "WindowsInput.h"
#include "Core/Application.h"

namespace Letgen
{
	Input* Input::s_Instance = new WindowsInput;
	
	bool WindowsInput::IsKeyPressedImpl(const int keycode)
	{
		const auto window = static_cast<GLFWwindow*>(
			Application::Get().GetWindow().GetNativeWindow());

		const auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::IsKeyReleasedImpl(const int keycode)
	{
		const auto window = static_cast<GLFWwindow*>(
			Application::Get().GetWindow().GetNativeWindow());

		const auto state = glfwGetKey(window, keycode);
		return state == GLFW_RELEASE;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(int button)
	{
		const auto window = static_cast<GLFWwindow*>(
			Application::Get().GetWindow().GetNativeWindow());

		const auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	bool WindowsInput::IsMouseButtonReleasedImpl(int button)
	{
		const auto window = static_cast<GLFWwindow*>(
			Application::Get().GetWindow().GetNativeWindow());

		const auto state = glfwGetMouseButton(window, button);
		return state == GLFW_RELEASE;
	}

	std::pair<float, float> WindowsInput::GetMousePositionImpl()
	{
		const auto window = static_cast<GLFWwindow*>(
			Application::Get().GetWindow().GetNativeWindow());

		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);
		return { static_cast<float>(xPos), static_cast<float>(yPos) };
	}

	float WindowsInput::GetMouseXImpl()
	{
		auto [x, y] = GetMousePositionImpl();
		return x;
	}

	float WindowsInput::GetMouseYImpl()
	{
		auto [x, y] = GetMousePositionImpl();
		return y;
	}
}
