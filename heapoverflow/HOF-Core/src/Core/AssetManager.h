/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Project: CS250
Author: Junwoo Seo
-----------------------------------------------------------------*/
#pragma once
#include "ShaderManager.h"
#include <memory>

#include "Graphics/Mesh.h"

namespace hof
{
	class AssetManager
	{
	public:
		static void Init();
		static std::shared_ptr<ShaderManager> GetShaderManager();

		static void LoadObj(const std::string& mesh_name, const std::string& mesh_path, bool print_info = false);
		static std::shared_ptr<Mesh> GetMesh(const std::string& str);

	};
}
