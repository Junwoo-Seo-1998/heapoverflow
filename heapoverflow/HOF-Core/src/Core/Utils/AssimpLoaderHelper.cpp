/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Project: CS250
Author: Junwoo Seo
-----------------------------------------------------------------*/
#include "AssimpLoaderHelper.h"
#include "Core/VertexArray.h"

void LoadModel(const std::string& filePath, std::shared_ptr<hof::Mesh> mesh)
{

	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(filePath, aiProcess_Triangulate);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
	{
		std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
		return;
	}
	ProcessNode(mesh, scene->mRootNode, scene);
}

void ProcessNode(std::shared_ptr<hof::Mesh> mesh, aiNode* node, const aiScene* scene)
{
	for (unsigned int i=0; i< node->mNumMeshes; ++i)
	{
		aiMesh* ai_mesh = scene->mMeshes[i];
		mesh->GetMeshes().push_back(ProcessMesh(ai_mesh, scene));
	}
	
	for (unsigned int i = 0; i < node->mNumChildren; ++i)
	{
		ProcessNode(mesh, node->mChildren[i], scene);
	}
}

std::shared_ptr<hof::SubMesh> ProcessMesh(aiMesh* loaded_mesh, [[maybe_unused]] const aiScene* scene)
{
	std::shared_ptr<hof::SubMesh> sub_mesh = std::make_shared<hof::SubMesh>();
	sub_mesh->GetVertices().reserve(loaded_mesh->mNumVertices);
	
	for (unsigned int i = 0; i < loaded_mesh->mNumVertices; ++i)
	{
		hof::Vertex new_vertex;

		new_vertex.position.x = loaded_mesh->mVertices[i].x;
		new_vertex.position.y = loaded_mesh->mVertices[i].y;
		new_vertex.position.z = loaded_mesh->mVertices[i].z;

		
		if(loaded_mesh->HasNormals())
		{
			new_vertex.normal.x = loaded_mesh->mNormals[i].x;
			new_vertex.normal.y = loaded_mesh->mNormals[i].y;
			new_vertex.normal.z = loaded_mesh->mNormals[i].z;
		}

		sub_mesh->GetVertices().push_back(new_vertex);
	}

	for (unsigned int i = 0; i < loaded_mesh->mNumFaces; ++i)
	{
		aiFace face = loaded_mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; ++j)
			sub_mesh->GetIndices().push_back(face.mIndices[j]);
	}

	sub_mesh->SetVertexArray(std::make_shared<hof::VertexArray>());
	
	std::shared_ptr<hof::VertexBuffer> vertex_buffer = 
		std::make_shared<hof::VertexBuffer>(sub_mesh->GetVertices().data(), sub_mesh->GetNumOfVertices() * sizeof(hof::Vertex));
	vertex_buffer->DescribeData({
		{hof::DataType::Float3,0},
		{hof::DataType::Float3,1},
	});
	
	sub_mesh->GetVertexArray()->AddVertexBuffer(vertex_buffer);

	std::shared_ptr<hof::IndexBuffer>index_buffer =
		std::make_shared<hof::IndexBuffer>(sub_mesh->GetIndices().data(), sub_mesh->GetNumOfIndices());

	sub_mesh->GetVertexArray()->AddIndexBuffer(index_buffer);
	
	return sub_mesh;
}

