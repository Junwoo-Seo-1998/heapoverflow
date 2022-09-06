/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Project: CS250
Author: Junwoo Seo
-----------------------------------------------------------------*/
#include "VertexArray.h"
#include "GL/glew.h"

namespace hof
{
	VertexArray::VertexArray()
	{
		glCreateVertexArrays(1, &m_VertexArrayID);
	}

	VertexArray::~VertexArray()
	{
		glBindVertexArray(0);
		glDeleteVertexArrays(1, &m_VertexArrayID);
	}

	void VertexArray::Bind() const
	{
		glBindVertexArray(m_VertexArrayID);
	}

	void VertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void VertexArray::AddVertexBuffer(std::shared_ptr<VertexBuffer> vertex_buffer)
	{
		glBindVertexArray(m_VertexArrayID);
		vertex_buffer->Bind();

		const auto& described_Data = vertex_buffer->GetDescribedData();
		for (const auto& element : described_Data)
		{
			glEnableVertexAttribArray(element.m_LayoutLocation);
			glVertexAttribPointer
			(
				element.m_LayoutLocation,
				element.m_ElementCount,
				element.ShaderDataTypeToOpenGLBaseType(),
				element.m_Normalize ? GL_TRUE : GL_FALSE,
				described_Data.GetStride(),
				(const void*)element.m_Offset
			);
		}
		m_VertexBuffers.push_back(vertex_buffer);
	}

	void VertexArray::AddIndexBuffer(std::shared_ptr<IndexBuffer> index_buffer)
	{
		glBindVertexArray(m_VertexArrayID);
		index_buffer->Bind();

		m_IndexBuffers = index_buffer;
	}
}
