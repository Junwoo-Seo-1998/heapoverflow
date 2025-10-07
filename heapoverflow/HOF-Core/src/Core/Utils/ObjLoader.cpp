/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Project: CS250
Author: Junwoo Seo
-----------------------------------------------------------------*/
#include "ObjLoader.h"
#include <iostream>
#include <unordered_map>
#include "tiny_obj_loader.h"
#include "Core/Graphics/Mesh.h"

namespace hof
{
	// Helper struct for vertex packing
	struct PackedVertexHasher {
		std::size_t operator()(const PackedVertex& v) const {
			// A simple hash combination
			auto h1 = std::hash<float>()(v.position.x) ^ std::hash<float>()(v.position.y) ^ std::hash<float>()(v.position.z);
			auto h2 = std::hash<float>()(v.normal.x) ^ std::hash<float>()(v.normal.y) ^ std::hash<float>()(v.normal.z);
			return h1 ^ (h2 << 1);
		}
	};

	void LoadObj(const std::string& file_path, Mesh& mesh, bool print_info)
	{
		tinyobj::ObjReader reader;
		if (!reader.ParseFromFile(file_path)) {
			if (!reader.Error().empty()) {
				std::cerr << "TinyObjReader: " << reader.Error();
			}
			return;
		}

		if (!reader.Warning().empty()) {
			std::cout << "TinyObjReader: " << reader.Warning();
		}

		auto& attrib = reader.GetAttrib();
		auto& shapes = reader.GetShapes();

		// Loop over shapes
		for (size_t s = 0; s < shapes.size(); s++)
		{
			auto sub_mesh = std::make_shared<SubMesh>();
			std::unordered_map<PackedVertex, uint32_t, PackedVertexHasher> unique_vertices;

			// Loop over faces(polygon)
			size_t index_offset = 0;
			for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++)
			{
				size_t fv = size_t(shapes[s].mesh.num_face_vertices[f]);

				// Loop over vertices in the face.
				for (size_t v = 0; v < fv; v++)
				{
					tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];

					PackedVertex vertex = {};

					vertex.position = {
						attrib.vertices[3 * size_t(idx.vertex_index) + 0],
						attrib.vertices[3 * size_t(idx.vertex_index) + 1],
						attrib.vertices[3 * size_t(idx.vertex_index) + 2]
					};

					if (idx.normal_index >= 0) {
						vertex.normal = {
							attrib.normals[3 * size_t(idx.normal_index) + 0],
							attrib.normals[3 * size_t(idx.normal_index) + 1],
							attrib.normals[3 * size_t(idx.normal_index) + 2]
						};
					}

					if (unique_vertices.count(vertex) == 0)
					{
						unique_vertices[vertex] = static_cast<uint32_t>(sub_mesh->GetVertices().size());
						sub_mesh->GetVertices().push_back({ vertex.position, vertex.normal });
					}
					sub_mesh->GetIndices().push_back(unique_vertices[vertex]);
				}
				index_offset += fv;
			}

			// Create VertexArray for the submesh
			if (!sub_mesh->GetVertices().empty() && !sub_mesh->GetIndices().empty())
			{
				auto va = std::make_shared<VertexArray>();
				auto vb = std::make_shared<VertexBuffer>(sub_mesh->GetVertices().data(), sub_mesh->GetVertices().size() * sizeof(Vertex));
				vb->DescribeData({
					{DataType::Float3, 0}, // position
					{DataType::Float3, 1}  // normal
				});
				va->AddVertexBuffer(vb);

				auto ib = std::make_shared<IndexBuffer>(sub_mesh->GetIndices().data(), sub_mesh->GetIndices().size());
				va->AddIndexBuffer(ib);

				sub_mesh->SetVertexArray(va);
			}

			mesh.GetMeshes().push_back(sub_mesh);
		}
	}
}
