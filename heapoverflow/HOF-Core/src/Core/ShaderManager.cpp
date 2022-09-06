/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Project: CS250
Author: Junwoo Seo
-----------------------------------------------------------------*/
#include "ShaderManager.h"

namespace hof
{
	ShaderManager::ShaderManager()
	{
	}

	ShaderManager::~ShaderManager()
	{
	}

	void ShaderManager::Add(const std::shared_ptr<Shader>& shader)
	{
		auto& name = shader->GetName();
		m_Shaders[name] = shader;
	}

	void ShaderManager::Load(const std::string& name, const std::string& vert, const std::string& frag)
	{
		std::shared_ptr<Shader> shader = std::make_shared<Shader>(name, vert, frag);
		Add(shader);
	}

	const std::shared_ptr<Shader>& ShaderManager::Get(const std::string& name) const
	{
		return m_Shaders.at(name);
	}
}
