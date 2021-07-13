#pragma once
#include "Core/Core.h"
#include "KeyCodes.h"
#include "MouseButton.h"

namespace Letgen
{
	class LETGEN_API Input
	{
	public:	
		static bool IsKeyPressed(const KeyCode keycode)
		{
			return s_Instance->IsKeyPressedImpl(static_cast<int>(keycode));
		}
		static bool IsKeyReleased(const KeyCode keycode)
		{
			return s_Instance->IsKeyReleasedImpl(static_cast<int>(keycode));
		}
		static bool IsMouseButtonPressed(const MouseButton button)
		{
			return s_Instance->IsKeyReleasedImpl(static_cast<int>(button));
		}
		static bool IsMouseButtonReleased(const MouseButton button)
		{
			return s_Instance->IsKeyReleasedImpl(static_cast<int>(button));
		}
		static std::pair<float, float> GetMousePosition()
		{
			return s_Instance->GetMousePositionImpl();
		}
		static float GetMouseX()
		{
			return s_Instance->GetMouseXImpl();
		}
		static float GetMouseY()
		{
			return s_Instance->GetMouseYImpl();
		}
		
	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0;
		virtual bool IsKeyReleasedImpl(int keycode) = 0;
		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual bool IsMouseButtonReleasedImpl(int button) = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;
	private:
		static Input* s_Instance;
	};
}
