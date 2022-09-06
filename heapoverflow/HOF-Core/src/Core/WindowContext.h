/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Project: CS250
Author: Junwoo Seo
-----------------------------------------------------------------*/
#pragma once

struct GLFWwindow;
namespace hof
{
	class WindowContext
	{
	public:
		static void SetOpenGLVersion(int major, int minor);

		
		WindowContext(GLFWwindow* window);
		void Init();
		void SwapBuffers();
	private:
		GLFWwindow* m_Window;
	};
}