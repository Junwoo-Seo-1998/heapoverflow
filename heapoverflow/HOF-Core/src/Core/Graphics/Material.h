/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Project: CS250
Author: Junwoo Seo
-----------------------------------------------------------------*/
#pragma once
#include <memory>
#include "Core/Utils/Utils.h"
namespace hof
{
	class Shader;

	enum class MaterialFlag
	{
		None=BIT(0),
	};

	
	class Material
	{
	public:
		Material(std::shared_ptr<Shader> shader);
		
		void Bind();
		std::shared_ptr<Shader> GetShader() const;
	private:
		std::shared_ptr<Shader> m_Shader;
	};
}
