// C++ STL
#include <iostream>

// 
#include "App.hpp" 
#define Version_ "0.4.0"
const int WIDTH = 1136;
const int HEIGHT = 640;

int main(int argc, char ** argv)
{
	
	// Create Game Object
	//
	Engine::App* app = new Engine::App("Asteroids V 0.4.0", WIDTH, HEIGHT);	

	// Initialize game
	//
	if(!app->Init())
	{
		std::cout << "App Init error!\n";
		return -1;
	}	

	// Execute game
	//
	app->Execute();

	// Delete game object
	//
	delete app;

	return 0;
}