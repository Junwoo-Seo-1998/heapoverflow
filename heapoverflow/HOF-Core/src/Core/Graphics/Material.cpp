/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Project: CS250
Author: Junwoo Seo
-----------------------------------------------------------------*/
#include "Material.h"
#include "Core/Renderer.h"
#include "Core/Shader.h"
namespace hof
{
	Material::Material(std::shared_ptr<Shader> shader)
		:m_Shader(std::move(shader))
	{}

	void Material::Bind()
	{
		m_Shader->Bind();
	}

	std::shared_ptr<Shader> Material::GetShader() const
	{
		return m_Shader;
	}
}
