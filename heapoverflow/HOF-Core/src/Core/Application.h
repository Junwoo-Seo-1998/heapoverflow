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
#include "ApplicationWindow.h"
#include "ImGuiLayer.h"
#include "LayerManager.h"
int main(int argc, char** argv);
namespace hof
{
	class WindowCloseEvent;
	class WindowResizeEvent;
	class Layer;
	class  Application
	{
	public:
		Application(const std::string& name = "Heap Over Flow!");
		~Application();
		
		ApplicationWindow& GetWindow() { return *m_Window; }
		static Application& Get() { return *s_Instance; }
		
		virtual void OnInit() {}
		virtual void OnUpdate([[maybe_unused]]float dt) {}
		virtual void OnShutdown() {}
		void OnEvent(Event& event);
		
		void PushLayer(std::shared_ptr<Layer> layer);
		void PopLayer(std::shared_ptr<Layer> layer);
		void PushOverlay(std::shared_ptr<Layer> overlay);
		void PopOverlay(std::shared_ptr<Layer> overlay);
	private:
		bool OnWindowClose(WindowCloseEvent& event);
		bool OnWindowResize(WindowResizeEvent& event);
		
		void Run();
		void Quit();
	private:
		static Application* s_Instance;
		std::shared_ptr<ImGuiLayer> m_ImGuiLayer;
		bool m_Running = true;
		float m_LastTime = 0.f;
		std::unique_ptr<ApplicationWindow> m_Window;
		LayerManager m_LayerManager;
		
		friend int ::main(int argc, char** argv);
	};
}
hof::Application* CoreMain();
