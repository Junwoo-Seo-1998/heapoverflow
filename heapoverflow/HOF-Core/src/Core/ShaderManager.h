/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Project: CS250
Author: Junwoo Seo
-----------------------------------------------------------------*/
#pragma once
#include "Shader.h"
#include <unordered_map>
#include <string>
#include <memory>

namespace hof
{
	class ShaderManager
	{
	public:
		ShaderManager();
		~ShaderManager();

		void Add(const std::shared_ptr<Shader>& shader);
		void Load(const std::string& name, const std::string& vert, const std::string& frag);

		const std::shared_ptr<Shader>& Get(const std::string& name) const;
	private:
		std::unordered_map<std::string, std::shared_ptr<Shader>> m_Shaders;
	};
}
