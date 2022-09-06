/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Project: CS250
Author: Junwoo Seo
-----------------------------------------------------------------*/
#include "Buffers.h"
#include "GL/glew.h"
namespace hof
{
	DataAndLayoutLocation::DataAndLayoutLocation(DataType data, unsigned layout_location, [[maybe_unused]] bool normalize)
		:m_DataType(data), m_LayoutLocation(layout_location), m_Size(0), m_ElementCount(0), m_Offset(0)
	{

		//compute size of data 
		switch (data)
		{
			case DataType::Bool:	m_Size = 4;			 break;
			case DataType::Int:		m_Size = 4;			 break;
			case DataType::Int2:	m_Size = 4 * 2;		 break;
			case DataType::Int3:	m_Size = 4 * 3;		 break;
			case DataType::Int4:	m_Size = 4 * 4;		 break;
			case DataType::Float:   m_Size = 4;			 break;
			case DataType::Float2:	m_Size = 4 * 2;		 break;
			case DataType::Float3:	m_Size = 4 * 3;		 break;
			case DataType::Float4:	m_Size = 4 * 4;		 break;
			case DataType::Mat3:	m_Size = 4 * 3 * 3;	 break;
			case DataType::Mat4:	m_Size = 4 * 4 * 4;	 break;
		}

		//get element count 
		switch (data)
		{
			case DataType::Bool:	m_ElementCount = 1; 	break;
			case DataType::Int:		m_ElementCount = 1;		break;
			case DataType::Int2:	m_ElementCount = 2;		break;
			case DataType::Int3:	m_ElementCount = 3;		break;
			case DataType::Int4:	m_ElementCount = 4;		break;
			case DataType::Float:	m_ElementCount = 1;		break;
			case DataType::Float2:	m_ElementCount = 2;		break;
			case DataType::Float3:	m_ElementCount = 3;		break;
			case DataType::Float4:	m_ElementCount = 4;		break;
			case DataType::Mat3:	m_ElementCount = 3 * 3;	break;
			case DataType::Mat4:	m_ElementCount = 4 * 4;	break;
		}
	}

	GLenum DataAndLayoutLocation::ShaderDataTypeToOpenGLBaseType() const 
	{
		switch (m_DataType)
		{
			case DataType::Bool:		return GL_BOOL;
			case DataType::Int:			return GL_INT;
			case DataType::Int2:		return GL_INT;
			case DataType::Int3:		return GL_INT;
			case DataType::Int4:		return GL_INT;
			case DataType::Float:		return GL_FLOAT;
			case DataType::Float2:		return GL_FLOAT;
			case DataType::Float3:		return GL_FLOAT;
			case DataType::Float4:		return GL_FLOAT;
			case DataType::Mat3:		return GL_FLOAT;
			case DataType::Mat4:		return GL_FLOAT;
		}
		return 0;
	}


	DescribeData::DescribeData(const std::initializer_list<DataAndLayoutLocation>& described_data)
		:m_DescribedData(described_data)
	{
		//compute offset and stride
		unsigned int offset = 0;
		m_Stride = 0;
		for(auto& data : m_DescribedData)
		{
			data.m_Offset = offset;
			offset += data.m_Size;
			m_Stride += data.m_Size;
		}
	}

	VertexBuffer::VertexBuffer(unsigned size)
	{
		glCreateBuffers(1, &m_BufferID);
		glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
	}

	VertexBuffer::VertexBuffer(void* vertices, unsigned size)
	{
		glCreateBuffers(1, &m_BufferID);
		glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &m_BufferID);
	}

	void VertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
	}

	void VertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void VertexBuffer::BufferData(const void* data, unsigned size)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}

	IndexBuffer::IndexBuffer(unsigned* indices, unsigned count)
		:m_Count(count)
	{
		glCreateBuffers(1, &m_BufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned) * count, indices, GL_DYNAMIC_DRAW);
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &m_BufferID);
	}

	void IndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
	}

	void IndexBuffer::Unbind() const 
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
	}
}
