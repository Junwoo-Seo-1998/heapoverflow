/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Project: CS250
Author: Junwoo Seo
-----------------------------------------------------------------*/
#pragma once
#include "Core/Application.h"

extern hof::Application* CoreMain();

#include <filesystem>
#include "Core/Utils/FileSystem.h"

int main(int argc, char** argv) try
{
	hof::Utils::G_ExecutableDirectory = std::filesystem::path(argv[0]).parent_path();

	auto app = CoreMain();
	app->OnInit();
	app->Run();
	app->OnShutdown();
	delete app;
}
catch(std::string error_msg)
{
	std::cout << "error!!! : " << error_msg << std::endl;
}
