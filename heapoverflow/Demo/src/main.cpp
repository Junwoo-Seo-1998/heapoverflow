/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Project: CS250
Author: Junwoo Seo
-----------------------------------------------------------------*/
#include "EntryPoint.h"
#include "HOF.h"
#include <memory>


#include "Layer/DemoLayer.h"
#include "Layer/Common/CommonSceneGUILayer.h"
#include "Scene/FogScene.h"
#include "Scene/GrassScene.h"
#include "Scene/ShadowScene.h"
#include "Scene/ToonScene.h"

class DemoApplication :public hof::Application
{
public:
	virtual void OnInit() override
	{
		using namespace hof;

		//order matters
		AssetManager::LoadObj("Plane", "resource/obj/plane.obj");
		AssetManager::LoadObj("Cube", "resource/obj/cube.obj");
		AssetManager::LoadObj("Monkey", "resource/obj/suzanne.obj");


		AssetManager::GetShaderManager()->Add(std::make_shared<Shader>("SimpleColorShader", "resource/shader/SimpleColor/SimpleColor.vert", "resource/shader/SimpleColor/SimpleColor.frag"));
		AssetManager::GetShaderManager()->Add(std::make_shared<Shader>("ToonShader", "resource/shader/Toon/Toon.vert", "resource/shader/Toon/Toon.frag"));
		AssetManager::GetShaderManager()->Add(std::make_shared<Shader>("FogShader", "resource/shader/Fog/Fog.vert", "resource/shader/Fog/Fog.frag"));
		
		AssetManager::GetShaderManager()
		->Add(std::make_shared<Shader>("GrassGroundShader", 
			"resource/shader/Grass/GrassGround.vert", 
			"resource/shader/Grass/GrassGround.frag",
			"resource/shader/Grass/GrassGround.tesc",
			"resource/shader/Grass/GrassGround.tese"));
		AssetManager::GetShaderManager()
		->Add(std::make_shared<Shader>("GrassShader", 
			"resource/shader/Grass/Grass.vert", 
			"resource/shader/Grass/Grass.frag",
			"resource/shader/Grass/Grass.tesc",
			"resource/shader/Grass/Grass.tese",
			"resource/shader/Grass/Grass.geom"
			));


		AssetManager::GetShaderManager()
			->Add(std::make_shared<Shader>("ShadowShader",
				"resource/shader/Shadow/Shadow.vert",
				"resource/shader/Shadow/Shadow.frag"
				));
		
		//order matters 
		SceneManager::AddScene<ToonScene>("ToonDemo");
		SceneManager::AddScene<FogScene>("FogDemo");
		SceneManager::AddScene<GrassScene>("GrassDemo");
		SceneManager::AddScene<ShadowScene>("ShadowDemo");

		SceneManager::LoadScene("ToonDemo");

		//order matters 
		PushLayer(std::make_shared<DemoLayer>());
		PushOverlay(std::make_shared<CommonSceneGUILayer>());
		
	}
	virtual void OnUpdate(float dt) override
	{
		hof::SceneManager::GetCurrentScene()->OnUpdate(dt);
	}
	
	virtual void OnShutdown() override
	{
		using namespace hof;
		
	}
private:
	
};


hof::Application* CoreMain()
{
	//defined entry point inside of hof-core lib. so that demo don't have to know about impl of application.

	return new DemoApplication();
}