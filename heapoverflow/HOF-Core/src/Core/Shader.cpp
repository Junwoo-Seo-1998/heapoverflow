/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Project: CS250
Author: Junwoo Seo
-----------------------------------------------------------------*/
#include "shader.h"
#include "GL/glew.h"
#include <fstream>
#include <iostream>
#include <vector>



#include "glm/gtc/type_ptr.hpp"

namespace hof
{
	Shader::Shader(const std::string& name, const std::string& vert, const std::string& frag, const std::string& tesc, const std::string& tese, const std::string& geom)
		:m_Name(name),m_ShaderFlag(ShaderFlag::None)
	{
		if(vert.empty())
		{
			static_assert(true, "vertex shader should exist!!");
			return;
		}

		if (frag.empty())
		{
			static_assert(true, "fragment shader should exist!!");
			return;
		}
		m_ShaderID = glCreateProgram();
		
		unsigned int vert_shader = CompileShader(vert, GL_VERTEX_SHADER);
		unsigned int frag_shader = CompileShader(frag, GL_FRAGMENT_SHADER);
		glAttachShader(m_ShaderID, vert_shader);
		SetFlag(ShaderFlag::VertexShader);
		glAttachShader(m_ShaderID, frag_shader);
		SetFlag(ShaderFlag::FragmentShader);
		
		unsigned int tesc_shader = 0;
		if(tesc.empty()==false)
		{
			tesc_shader = CompileShader(tesc, GL_TESS_CONTROL_SHADER);
			glAttachShader(m_ShaderID, tesc_shader);
			SetFlag(ShaderFlag::TessellationShader);
		}

		unsigned int tese_shader = 0;
		if(tese.empty()==false)
		{
			tese_shader = CompileShader(tese, GL_TESS_EVALUATION_SHADER);
			glAttachShader(m_ShaderID, tese_shader);
			SetFlag(ShaderFlag::TessellationShader);
		}

		unsigned int geom_shader = 0;
		if(geom.empty()==false)
		{
			geom_shader = CompileShader(geom, GL_GEOMETRY_SHADER);
			glAttachShader(m_ShaderID, geom_shader);
			SetFlag(ShaderFlag::GeometryShader);
		}
;
		glLinkProgram(m_ShaderID);
		
		glDeleteShader(vert_shader);
		glDeleteShader(frag_shader);

		if (tesc.empty() == false)
		{
			glDeleteShader(tesc_shader);
		}

		if (tese.empty() == false)
		{
			glDeleteShader(tese_shader);
		}

		if (geom.empty() == false)
		{
			glDeleteShader(geom_shader);
		}

		std::cout << "shader info (" << name << ")" << ": " << std::endl;

		// print linking errors if any
		int success = 0;
		glGetProgramiv(m_ShaderID, GL_LINK_STATUS, &success);
		if (!success)
		{
			char infoLog[512] = { 0, };
			glGetProgramInfoLog(m_ShaderID, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}

		
		ParsingData();
		std::cout << std::endl;
		std::cout << std::endl;
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_ShaderID);
	}

	const std::string& Shader::GetName() const
	{
		return m_Name;
	}

	void Shader::Bind() const
	{
		glUseProgram(m_ShaderID);
	}

	void Shader::Unbind() const
	{
		glUseProgram(0);
	}

	void Shader::SetInt(const std::string& name, int value)
	{
		GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
		if (location == -1)
		{
			std::cout << "error on shader location! - " << name << std::endl;
			return;
		}
		glUniform1i(location, value);
	}

	void Shader::SetFloat(const std::string& name, float value)
	{
		GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
		if (location == -1)
		{
			std::cout << "error on shader location! - " << name << std::endl;
			return;
		}
		glUniform1f(location, value);
	}

	void Shader::SetFloat3(const std::string& name, const glm::vec3& value)
	{
		GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
		if (location == -1)
		{
			std::cout << "error on shader location! - " << name << std::endl;
			return;
		}
		glUniform3f(location, value.x, value.y, value.z);
	}

	void Shader::SetFloat4(const std::string& name, const glm::vec4& value)
	{
		GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
		if (location == -1)
		{
			std::cout << "error on shader location! - " << name << std::endl;
			return;
		}
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}

	void Shader::SetMat4(const std::string& name, const glm::mat4& value)
	{
		GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
		//assert(location!=-1, "failed to find");
		if(location==-1)
		{
			std::cout << "error on shader location! - "<<name<<std::endl;
			return;
		}
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}

	void Shader::ParsingData()
	{
		int num_of_attr = 0;
		glGetProgramiv(m_ShaderID, GL_ACTIVE_ATTRIBUTES, &num_of_attr);
		int num_of_attr_max_len = 0;
		glGetProgramiv(m_ShaderID, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &num_of_attr_max_len);
		
		for (int i=0; i<num_of_attr; ++i)
		{
			
			char* str = new char[num_of_attr_max_len];
			memset(str, 0, sizeof(char)* num_of_attr_max_len);
			int len = 0;
			int size = 0;
			GLenum  type = 0;
			glGetActiveAttrib(m_ShaderID, i, num_of_attr_max_len, &len, &size, &type, str);
			std::cout << str << std::endl;
			delete[] str;
		}

		int num_of_uniforms = 0;
		glGetProgramiv(m_ShaderID, GL_ACTIVE_UNIFORMS, &num_of_uniforms);
		int num_of_uniforms_max_len = 0;
		glGetProgramiv(m_ShaderID, GL_ACTIVE_UNIFORM_MAX_LENGTH, &num_of_uniforms_max_len);
		for (int i = 0; i < num_of_uniforms; ++i)
		{
			char* str = new char[num_of_uniforms_max_len];
			memset(str, 0, sizeof(char) * num_of_uniforms_max_len);
			int len = 0;
			int size = 0;
			GLenum  type = 0;
			glGetActiveUniform(m_ShaderID, i, num_of_uniforms_max_len, &len, &size, &type, str);
			std::cout << str << std::endl;
			delete[] str;
		}
	}

	bool Shader::GetFlag(ShaderFlag flag_to_comp) const
	{
		return static_cast<unsigned int>(m_ShaderFlag) & static_cast<unsigned int>(flag_to_comp);
	}

	void Shader::SetFlag(ShaderFlag flag, bool value)
	{
		if(value)
		{
			m_ShaderFlag = static_cast<ShaderFlag>(static_cast<unsigned int>(m_ShaderFlag) | static_cast<unsigned int>(flag));
		}
		else
		{
			m_ShaderFlag = static_cast<ShaderFlag>(static_cast<unsigned int>(m_ShaderFlag) & (~static_cast<unsigned int>(flag)));
		}
	}

	unsigned Shader::CompileShader(const std::string& src, unsigned shader_enum)
	{
		std::cout << "Compile : " << src.substr(src.find_last_of('/')+1)<<std::endl;
		
		std::ifstream src_stream(src);
		std::string shader_src_string;
		if (src_stream.is_open())
		{
			src_stream.seekg(0, std::ios::end);

			int size = static_cast<int>(src_stream.tellg());

			shader_src_string.resize(size);

			src_stream.seekg(0, std::ios::beg);

			src_stream.read(shader_src_string.data(), size);
		}
		
		unsigned int shader_id = glCreateShader(shader_enum);
		const char* shader_src_cstr = shader_src_string.c_str();

		glShaderSource(shader_id, 1, &shader_src_cstr, 0);
		glCompileShader(shader_id);

		int is_ok;
		char info_log[512] = { 0, };
		glGetShaderiv(shader_id, GL_COMPILE_STATUS, &is_ok);
		if (!is_ok)
		{
			glGetShaderInfoLog(shader_id, 512, NULL, info_log);
			const std::string shader_name = src.substr(src.find_last_of('/')+1);
			std::cout << shader_name << " compile error: " << info_log << std::endl;
		}
		
		return shader_id;
	}

}
