#pragma once
#include "Letgen/Core/Core.h"
#include "Letgen/Core/Layer.h"

namespace Letgen
{
	class LETGEN_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() override = default;

		void OnAttach() override;
		void OnDetach() override;
		void OnEvent(Event& event) override;
		void OnImGuiRender() override;

		void SetDarkThemeColors();
		
		void Begin();
		void End();
		void BlockEvents(bool value);
	private:
		bool m_IsBlockingEvents = true;
	};
}
