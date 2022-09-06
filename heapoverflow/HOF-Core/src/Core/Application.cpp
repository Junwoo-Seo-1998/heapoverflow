/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Project: CS250
Author: Junwoo Seo
-----------------------------------------------------------------*/
#include "Application.h"

#include <iostream>

#include "Renderer.h"
#include "GLFW/glfw3.h"
#include "LayerManager.h"
#include "AssetManager.h"
#include "Input.h"
#include "Event/Event.h"
#include "Event/ApplicationEvents/ApplicationEvent.h"

namespace hof
{
	Application* Application::s_Instance = nullptr;
	
	Application::Application(const std::string& name)
	{
		s_Instance = this;
		m_Window = std::make_unique<ApplicationWindow>(WindowProps(name));
		m_Window->SetEventCallbackFunction(BIND_EVENT_FUNCTION(OnEvent));
		Renderer::Init();
		AssetManager::Init();
		m_ImGuiLayer = std::make_shared<ImGuiLayer>();
		PushOverlay(m_ImGuiLayer);
		Renderer::SetClearColor({ 1.f,0.f,0.f,1.f });
	}

	Application::~Application()
	{
		Renderer::Shutdown();
	}

	void Application::OnEvent(Event& event)
	{
		EventDispatcher  dispatcher(event);
		//todo: impl close window func
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FUNCTION(OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FUNCTION(OnWindowResize));

		auto& overlay = m_LayerManager.GetOverLays();
		for (auto it = overlay.rbegin(); it != overlay.rend(); ++it)
		{
			if (event.m_Handled)
				break;
			(*it)->OnEvent(event);
		}

		auto& layers = m_LayerManager.GetLayers();
		for (auto it = layers.rbegin(); it != layers.rend(); ++it)
		{
			if (event.m_Handled)
				break;
			(*it)->OnEvent(event);
		}
	}

	void Application::PushLayer(std::shared_ptr<Layer> layer)
	{
		m_LayerManager.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PopLayer(std::shared_ptr<Layer> layer)
	{
		m_LayerManager.PopLayer(layer);
		
	}

	void Application::PushOverlay(std::shared_ptr<Layer> overlay)
	{
		m_LayerManager.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::PopOverlay(std::shared_ptr<Layer> overlay)
	{
		m_LayerManager.PopOverlay(overlay);
	}

	bool Application::OnWindowClose(WindowCloseEvent& /*event*/)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& event)
	{
		auto [width, height] = event.GetWidthAndHeight();
		
		if (width == 0 || height == 0)
		{
			return false;
		}

		std::cout << event.GetEventNameString() << std::endl;
		
		Renderer::SetViewport(width, height);
		return false;
	}

	void Application::Run()
	{
		Input::SetLastMousePosition();
		while (m_Running)
		{
			float time = (float)glfwGetTime();
			float dt = time - m_LastTime;
			m_LastTime = time;
			//update here
			OnUpdate(dt);



			for (const std::shared_ptr<Layer>& layer : m_LayerManager.GetLayers())
				layer->OnUpdate(dt);

			for (const std::shared_ptr<Layer>& layer : m_LayerManager.GetOverLays())
				layer->OnUpdate(dt);

			m_ImGuiLayer->Begin();
			for (const std::shared_ptr<Layer>& layer : m_LayerManager.GetLayers())
				layer->OnGuiRender();
			for (const std::shared_ptr<Layer>& layer : m_LayerManager.GetOverLays())
				layer->OnGuiRender();
			m_ImGuiLayer->End();

			m_LayerManager.ClearDeleteQueue();

			Input::SetLastMousePosition();
			//glfw window updates
			m_Window->Update();

		}
	}

	void Application::Quit()
	{
		m_Running = false;
	}

}

