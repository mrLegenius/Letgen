#include <Letgen.h>
#include <Letgen/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace Letgen
{
	class LetEditor : public Application
	{
	public:
		LetEditor() : Application("LetEditor")
		{
			PushLayer(new EditorLayer);
		}
		~LetEditor() = default;
	};

	Application* Letgen::CreateApplication()
	{
		return new LetEditor;
	}
}
