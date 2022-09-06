/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Project: CS250
Author: Junwoo Seo
-----------------------------------------------------------------*/
#include "WindowContext.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <iostream>
namespace hof
{
	void WindowContext::SetOpenGLVersion(int major, int minor)
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	}

	WindowContext::WindowContext(GLFWwindow* window)
		:m_Window(window)
	{
	}

	void WindowContext::Init()
	{
		glfwMakeContextCurrent(m_Window);
		GLenum err=glewInit();
		if (GLEW_OK != err)
		{
			//todo init failed
			std::cout << "Failed to init GLEW" << std::endl;
		}

		std::cout << "OpenGL Info :" << std::endl;
		std::cout << "    Version :" << glGetString(GL_VERSION) << std::endl;
		std::cout << "    Renderer:" << glGetString(GL_RENDERER) << std::endl;
	}

	void WindowContext::SwapBuffers()
	{
		glfwSwapBuffers(m_Window);
	}
}
