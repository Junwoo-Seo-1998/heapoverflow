/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Project: CS250
Author: Junwoo Seo
-----------------------------------------------------------------*/
#pragma once
#include <string>
#include <memory>

#include "WindowContext.h"
#include "Event/Event.h"

namespace hof
{
	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;
		bool VSync;
		WindowProps(const std::string& title = "Heap Over Flow!",
			uint32_t width = 1600,
			uint32_t height = 900, bool VSync = true)
			:Title(title), Width(width), Height(height), VSync(VSync)
		{}
	};
	
	class ApplicationWindow
	{
	public:
		using EventCallbackFunction = std::function<void(Event&)>;
		ApplicationWindow() = delete;
		ApplicationWindow(const WindowProps& windowProps) { Init(windowProps); }

		void* GetGLFWWindow() const { return m_WindowData.window; }
		
		bool IsVSyncOn() { m_WindowData.isVSyncOn; }
		std::pair<unsigned int, unsigned int> GetWidthHeight() const;
		unsigned int GetWidth() { return m_WindowData.width; }
		unsigned int GetHeight() { return m_WindowData.height; }

		void SetVSync(bool enable);

		void Update();

		void SetEventCallbackFunction(const EventCallbackFunction& callback);
		
	private:
		void Init(const WindowProps& windowProps);
		void Shutdown();
	private:
		struct WindowData
		{
			GLFWwindow* window = nullptr;
			std::shared_ptr<WindowContext> renderingContext;
			std::string title = "window";
			unsigned int width = 800;
			unsigned int height = 800;
			bool isVSyncOn = true;

			EventCallbackFunction eventCallback = nullptr;
		};
		WindowData m_WindowData;
	};
}
