//
// Created by cjp on 1/4/23.
//

#ifndef TERROIR_APPENTRY_H
#define TERROIR_APPENTRY_H

extern Terroir::Application* Terroir::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Terroir::CreateApplication();
	app->Init();
	delete app;
}

#endif //TERROIR_APPENTRY_H
