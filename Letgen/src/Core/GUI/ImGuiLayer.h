#pragma once
#include "Core/Core.h"
#include "Core/Layer.h"

namespace Letgen
{
	class LETGEN_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach() override;
		void OnDetach() override;
		void OnImGuiRender() override;
		
		void Begin();
		void End();
	};
}
