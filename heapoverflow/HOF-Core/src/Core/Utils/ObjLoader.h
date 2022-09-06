/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Project: CS250
Author: Junwoo Seo
-----------------------------------------------------------------*/
#pragma once
#include <map>
#include <vector>
#include <glm/glm.hpp>
#include <string>
namespace hof
{
	class Mesh;

	struct PackedVertex {
		glm::vec3 position;
		//glm::vec2 uv;
		glm::vec3 normal;
		bool operator<(const PackedVertex that) const {
			return memcmp(this, &that, sizeof(PackedVertex))>0;
		}
	};
	
	bool GetSameVertexIndex(PackedVertex& packed_vertex, std::map<PackedVertex, unsigned int> index_map, unsigned int& index);


	void PackVertex(std::vector<glm::vec3>& positions, std::vector<glm::vec3>& normals,
		std::vector<glm::vec3>& out_positions, std::vector<glm::vec3>& out_normals,
		std::vector<unsigned int>& out_indices);


	void LoadObj(const std::string& file_path, Mesh& mesh, bool print_info = false);
}
