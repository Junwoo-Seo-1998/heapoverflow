/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Project: CS250
Author: Junwoo Seo
-----------------------------------------------------------------*/
#pragma once
#include <initializer_list>
#include <vector>
#include "GL/glew.h"

namespace hof
{
	enum DataType
	{
		None = 0, Bool, Int, Int2, Int3, Int4, Float, Float2, Float3, Float4, Mat3, Mat4, 
	};

	struct DataAndLayoutLocation
	{
		DataType m_DataType;
		unsigned int m_LayoutLocation;
		unsigned int m_Size;
		unsigned int m_ElementCount;
		unsigned int m_Offset;
		bool m_Normalize;

		DataAndLayoutLocation() = delete;
		DataAndLayoutLocation(DataType data, unsigned int layout_location, bool normalize = false);
		GLenum ShaderDataTypeToOpenGLBaseType() const;
	};

	class DescribeData
	{
	public:
		DescribeData() {}
		DescribeData(const std::initializer_list<DataAndLayoutLocation>& described_data);
		
		unsigned int GetStride() const { return m_Stride; }

		std::vector<DataAndLayoutLocation>::iterator begin() { return m_DescribedData.begin(); }
		std::vector<DataAndLayoutLocation>::iterator end() { return m_DescribedData.end(); }
		std::vector<DataAndLayoutLocation>::const_iterator begin() const { return m_DescribedData.cbegin(); }
		std::vector<DataAndLayoutLocation>::const_iterator end() const { return m_DescribedData.cend(); }
	private:
		std::vector<DataAndLayoutLocation> m_DescribedData;
		unsigned int m_Stride;
	};

	
	class VertexBuffer
	{
	public:
		VertexBuffer(unsigned int size);
		VertexBuffer(void* vertices, unsigned int size);
		~VertexBuffer();

		void Bind() const;
		void Unbind() const;

		void BufferData(const void* data, unsigned int size);

		void DescribeData(const hof::DescribeData& described_Data) { m_DescribedData = described_Data; }
		const hof::DescribeData& GetDescribedData() const { return m_DescribedData; }
	private:
		unsigned int m_BufferID;
		hof::DescribeData m_DescribedData;
	};

	class IndexBuffer
	{
	public:
		IndexBuffer(unsigned int* indices, unsigned int count);
		~IndexBuffer();
		void Bind() const;
		void Unbind() const;

		unsigned int GetCount() const { return  m_Count; }

	private:
		unsigned int m_BufferID;
		unsigned int m_Count;
	};
}
