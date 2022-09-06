/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Project: CS250
Author: Junwoo Seo
-----------------------------------------------------------------*/
#pragma once
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "Core/Graphics/Mesh.h"
#include <string>
#include <iostream>
#include <memory>

void LoadModel(const std::string& filePath, std::shared_ptr<hof::Mesh> mesh);

void ProcessNode(std::shared_ptr<hof::Mesh> mesh, aiNode* node, const aiScene* scene);

std::shared_ptr<hof::SubMesh> ProcessMesh(aiMesh* loaded_mesh, const aiScene* scene);