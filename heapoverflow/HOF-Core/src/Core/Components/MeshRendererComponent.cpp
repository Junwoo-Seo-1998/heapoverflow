/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Project: CS250
Author: Junwoo Seo
-----------------------------------------------------------------*/
#include "MeshRendererComponent.h"

namespace hof
{
	MeshRendererComponent::MeshRendererComponent(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material, bool cast_shadow)
		:mesh(std::move(mesh)),cast_shadow(cast_shadow)
	{
		materials.push_back(material);
	}
}
