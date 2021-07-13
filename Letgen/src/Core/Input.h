#pragma once
#include "Core/Core.h"

namespace Letgen
{
	class LETGEN_API Input
	{
	public:	
		static bool IsKeyPressed(const int keycode)
		{
			return s_Instance->IsKeyPressedImpl(keycode);
		}
		static bool IsKeyReleased(const int keycode)
		{
			return s_Instance->IsKeyReleasedImpl(keycode);
		}
		static bool IsMouseButtonPressed(const int button)
		{
			return s_Instance->IsKeyReleasedImpl(button);
		}
		static bool IsMouseButtonReleased(const int button)
		{
			return s_Instance->IsKeyReleasedImpl(button);
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
