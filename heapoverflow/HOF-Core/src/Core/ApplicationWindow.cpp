/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Project: CS250
Author: Junwoo Seo
-----------------------------------------------------------------*/
#include "ApplicationWindow.h"

#include <iostream>



#include "Renderer.h"
#include "Event/ApplicationEvents/ApplicationEvent.h"
#include "Event/InputEvents/KeyBoardEvent.h"
#include "GLFW/glfw3.h"

namespace hof
{
	static bool GLFW_Initialization = false;

	std::pair<unsigned, unsigned> ApplicationWindow::GetWidthHeight() const
	{
		return { m_WindowData.width ,m_WindowData.height };
	}

	void ApplicationWindow::SetVSync(bool enable)
	{
		if (enable)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);
		m_WindowData.isVSyncOn = enable;
	}

	void ApplicationWindow::Update()
	{
		glfwPollEvents();
		m_WindowData.renderingContext->SwapBuffers();
	}

	void ApplicationWindow::SetEventCallbackFunction(const EventCallbackFunction& callback)
	{
		m_WindowData.eventCallback = callback;
	}

	void ApplicationWindow::Init(const WindowProps& windowProps)
	{
		if(!GLFW_Initialization)
		{
			int success = glfwInit();
			//set gl version
			WindowContext::SetOpenGLVersion(4, 5);
			GLFW_Initialization = true;
			if(success==0)
				return;
		}
		m_WindowData.title = windowProps.Title;
		m_WindowData.width = windowProps.Width;
		m_WindowData.height = windowProps.Height;
		m_WindowData.isVSyncOn = windowProps.VSync;

		
		
		
		m_WindowData.window = glfwCreateWindow(m_WindowData.width, m_WindowData.height, m_WindowData.title.c_str(), nullptr, nullptr);
		//todo: check window created
		if (m_WindowData.window == NULL) {
			std::cout << "failed to make window\n";
		}
		
		
		m_WindowData.renderingContext = std::make_shared<WindowContext>(m_WindowData.window);
		m_WindowData.renderingContext->Init();

		
		SetVSync(m_WindowData.isVSyncOn);


		//set glfw callback
		//so that we can use data of window in glfw call backs.
		glfwSetWindowUserPointer(m_WindowData.window, &m_WindowData);

		glfwSetKeyCallback(m_WindowData.window, [](GLFWwindow* window, int key, int /*scancode*/, int action, int /*mods*/)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyBoardPressedEvent event(static_cast<KeyCode>(key), 0);
					data.eventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					break;
				}
				case GLFW_REPEAT:
				{
					break;
				}
				}
			});
		
		glfwSetWindowSizeCallback(m_WindowData.window, [](GLFWwindow* window, int width, int height)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.width = width;
			data.height = height;

			WindowResizeEvent event(width, height);
			data.eventCallback(event);
		});

		glfwSetWindowCloseCallback(m_WindowData.window, [](GLFWwindow* window)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.eventCallback(event);

		});
	}

	void ApplicationWindow::Shutdown()
	{
	}
}
