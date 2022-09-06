/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Project: CS250
Author: Junwoo Seo
-----------------------------------------------------------------*/
#pragma once

namespace hof
{
	template <typename T>
	void SceneManager::AddScene(const std::string& str)
	{
		m_SceneFunctionMap.insert({ str,[]() -> std::shared_ptr<Scene>
		{
			return std::make_shared<T>();
		}});
	}
}