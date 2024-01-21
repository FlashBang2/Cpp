#ifndef SCENE_DATA_H
#define SCENE_DATA_H

#include"GenericScene.h"

class Example:public GenericScene
{
	public:
		Example();

		void Render(GLFWwindow* window, float deltaTime);
	private:
		std::vector<glm::vec3> objectsPositions;
};

#endif
