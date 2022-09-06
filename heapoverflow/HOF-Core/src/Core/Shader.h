/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Project: CS250
Author: Junwoo Seo
-----------------------------------------------------------------*/
#pragma once
#include <string>
#include <glm/glm.hpp>
#include "Utils/Utils.h"
namespace hof
{
	enum class ShaderFlag
	{
		None=BIT(0),
		VertexShader=BIT(1),
		FragmentShader=BIT(2),
		TessellationShader=BIT(3),
		GeometryShader=BIT(4),
	};
	
	class Shader
	{
	public:
		Shader(const std::string& name, const std::string& vert, const std::string& frag, const std::string& tesc = "", const std::string& tese = "", const std::string& geom = "");
		~Shader();
		const std::string& GetName() const;
		
		void Bind() const;
		void Unbind() const;
		void SetInt(const std::string& name, int value);
		void SetFloat(const std::string& name, float value);
		void SetFloat3(const std::string& name, const glm::vec3& value);
		void SetFloat4(const std::string& name, const glm::vec4& value);
		void SetMat4(const std::string& name, const glm::mat4& value);

		void ParsingData();

		bool GetFlag(ShaderFlag flag_to_comp) const;
	private:
		void SetFlag(ShaderFlag flag, bool value = true);
		unsigned int CompileShader(const std::string& src, unsigned int shader_enum);
		
	private:
		std::string m_Name;
		unsigned int m_ShaderID;
		ShaderFlag m_ShaderFlag;
	};
}
