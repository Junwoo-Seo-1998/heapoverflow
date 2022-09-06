/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Project: CS250
Author: Junwoo Seo
-----------------------------------------------------------------*/
#include "Mesh.h"

namespace hof
{
	std::vector<std::shared_ptr<SubMesh>>& Mesh::GetMeshes()
	{
		return m_Meshes;
	}
}