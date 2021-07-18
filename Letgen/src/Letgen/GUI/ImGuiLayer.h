#pragma once
#include "Letgen/Core/Core.h"
#include "Letgen/Core/Layer.h"

namespace Letgen
{
	class LETGEN_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		void OnAttach() override;
		void OnDetach() override;
		void OnImGuiRender() override;
		
		void Begin();
		void End();
	};
}
