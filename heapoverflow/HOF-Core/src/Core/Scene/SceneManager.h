/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Project: CS250
Author: Junwoo Seo
-----------------------------------------------------------------*/
#pragma once
#include "Scene.h"
#include <memory>
#include <map>
#include <string>
namespace hof
{
	class SceneManager
	{
	public:
		template<typename T>
		static void AddScene(const std::string& str);
		static void LoadScene(const std::string& str);
		static std::shared_ptr<Scene> GetCurrentScene();
	private:
		static std::shared_ptr<Scene> m_CurrentScene;
		static std::unordered_map < std::string, std::function<std::shared_ptr<Scene>(void)>> m_SceneFunctionMap;
	};
}

#include "SceneManager.hpp"