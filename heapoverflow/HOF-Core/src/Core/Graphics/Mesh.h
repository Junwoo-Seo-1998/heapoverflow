/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Project: CS250
Author: Junwoo Seo
-----------------------------------------------------------------*/
#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <memory>
#include <string>

#include "Core/VertexArray.h"

namespace hof
{
	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
	};
	
	
	class SubMesh
	{
	public:
		[[nodiscard]] std::vector<Vertex>& GetVertices() { return m_Vertices; }
		[[nodiscard]] unsigned int GetNumOfVertices() const { return static_cast<unsigned int>(m_Vertices.size()); }
		[[nodiscard]] std::vector<unsigned int>& GetIndices() { return m_Indices; }
		[[nodiscard]] unsigned int GetNumOfIndices() const { return static_cast<unsigned int>(m_Indices.size()); }

		void SetVertexArray(std::shared_ptr<VertexArray> vertex_array) { m_VertexArray = vertex_array; }
		[[nodiscard]] std::shared_ptr<VertexArray> GetVertexArray() const { return m_VertexArray; }
		
	private:
		std::vector<Vertex> m_Vertices;
		std::vector<unsigned int> m_Indices;

		std::shared_ptr<VertexArray> m_VertexArray;
	};

	class Mesh
	{
	public:
		[[nodiscard]] std::vector<std::shared_ptr<SubMesh>>& GetMeshes();


		std::vector<std::shared_ptr<SubMesh>>::iterator begin() { return m_Meshes.begin(); }
		std::vector<std::shared_ptr<SubMesh>>::iterator end() { return m_Meshes.end(); }
		std::vector<std::shared_ptr<SubMesh>>::reverse_iterator rbegin() { return m_Meshes.rbegin(); }
		std::vector<std::shared_ptr<SubMesh>>::reverse_iterator rend() { return m_Meshes.rend(); }
		
	private:
		std::vector<std::shared_ptr<SubMesh>> m_Meshes;
	};
}
