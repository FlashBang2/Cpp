#ifndef SCENE_H
#define SCENE_H

#include"Scenes/AdvanceExample.h"
#include"Scenes/Example.h"
#include"Scenes/Menu.h"

class SceneManager
{
	public:
		std::vector<GenericScene*> scenes;
		GLuint ID;
		bool flashlight;
		int width = 800, height = 800;

		SceneManager() {};
		SceneManager(GLuint currentScene);

		void Render(GLFWwindow* window, float deltaTime);
	private:
};

#endif 
