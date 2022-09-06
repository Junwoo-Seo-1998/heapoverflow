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
int main(int /*argc*/, char** /*argv*/) try
{
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
