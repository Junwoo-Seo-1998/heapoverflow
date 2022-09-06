/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Project: CS250
Author: Junwoo Seo
-----------------------------------------------------------------*/
#pragma once
#include "glm/glm.hpp"


//header to be used by Demo
#include "Core/Application.h"
#include "Core/Layer.h"
#include "Core/Scene/Scene.h"
#include "Core/Scene/SceneManager.h"
#include "Core/Entity/Entity.h"
#include "entt.hpp"
#include "Core/AssetManager.h"
#include "Core/Utils/ObjLoader.h"

//events
#include "Core/Event/Event.h"
#include "Core/Event/ApplicationEvents/ApplicationEvent.h"
#include "Core/Event/InputEvents/KeyBoardEvent.h"

//graphics
#include "Core/ShaderManager.h"
#include "Core/Renderer.h"
#include "Core/Shader.h"
#include "Core/VertexArray.h"
#include "Core/Buffers.h"
#include "Core/FrameBuffer.h"
#include "Core/Graphics/Material.h"

//components
#include "Core/Components/CameraComponent.h"
#include "Core/Components/MeshRendererComponent.h"
#include "Core/Components/TransformComponent.h"


//utils
#include "Core/Utils/Utils.h"


//input
#include "Core/Input.h"
