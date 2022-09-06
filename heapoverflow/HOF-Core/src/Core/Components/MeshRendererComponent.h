/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Project: CS250
Author: Junwoo Seo
-----------------------------------------------------------------*/
#pragma once
#include <memory>
#include <vector>

namespace hof
{
	class Mesh;
	class Material;
	struct MeshRendererComponent
	{
		MeshRendererComponent(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material, bool cast_shadow = false);

		std::shared_ptr<Mesh> mesh;
		std::vector<std::shared_ptr<Material>> materials;
		bool cast_shadow;
	};
}
