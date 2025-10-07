/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Project: CS250
Author: Junwoo Seo
-----------------------------------------------------------------*/
#include "AssetManager.h"
#include "Core/Utils/FileSystem.h"
#include "Utils/ObjLoader.h"
#include <string>
#include <iostream>


namespace hof
{
	namespace inner
	{
		static std::shared_ptr<ShaderManager> s_ShaderManager(nullptr);
		static std::unordered_map<std::string, std::shared_ptr<Mesh>> s_Meshs;
	}

	void AssetManager::Init()
	{
		inner::s_ShaderManager = std::make_shared<ShaderManager>();
	}

	std::shared_ptr<ShaderManager> AssetManager::GetShaderManager()
	{
		return  inner::s_ShaderManager;
	}

	void AssetManager::LoadObj(const std::string& mesh_name, const std::string& mesh_path, [[maybe_unused]] bool print_info)
	{
		auto absolute_path = hof::Utils::G_ExecutableDirectory / mesh_path;
		auto mesh = std::make_shared<Mesh>();
		hof::LoadObj(absolute_path.string(), *mesh, print_info);
		std::cout << "Loaded model: " << mesh_name << " from " << absolute_path.string() << std::endl;
		inner::s_Meshs.insert({ mesh_name, mesh });
	}

	std::shared_ptr<Mesh> AssetManager::GetMesh(const std::string& str)
	{
		return inner::s_Meshs[str];
	}
}
