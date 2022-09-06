/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Project: CS250
Author: Junwoo Seo
-----------------------------------------------------------------*/
#include "SceneManager.h"

namespace hof
{
	std::unordered_map<std::string, std::function<std::shared_ptr<Scene>(void)>> SceneManager::m_SceneFunctionMap;
	std::shared_ptr<Scene> SceneManager::m_CurrentScene{ nullptr };

	void SceneManager::LoadScene(const std::string& str)
	{
		if(m_CurrentScene)
		{
			m_CurrentScene->OnUnload();
		}
		m_CurrentScene = m_SceneFunctionMap[str]();
		if(m_CurrentScene)
		{
			m_CurrentScene->OnLoad();
		}
	}

	std::shared_ptr<Scene> SceneManager::GetCurrentScene()
	{
		return m_CurrentScene;
	}
}
