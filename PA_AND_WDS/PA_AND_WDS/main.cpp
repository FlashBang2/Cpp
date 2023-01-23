#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "model.h"
#include "Shader.h"
#include "Camera.h"

const unsigned int userWidth = 1920;
const unsigned int userHeight = 1080;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

int main() {

	unsigned int shaderProgram;

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(userWidth, userHeight, "BeeSimulator", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, userWidth, userHeight);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	Shader shader("VertexShader.glsl", "FragmentShader.glsl");

	Model model;
	model.loadModel("models/Bee/bee.gltf");

	glEnable(GL_DEPTH_TEST);

	Camera camera(userWidth, userHeight, glm::vec3(0.0f, 0.0f, 2.0f));

	shader.activate();

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.Inputs(window);

		camera.updateMatrix(45.0f, 0.1f, 500.0f);

		model.Render(shader);

		shader.setMat4("camMatrix", camera.cameraMatrix);

		processInput(window);
		
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	model.Cleanup();

	glfwDestroyWindow(window);

	glfwTerminate();
	return 0;
}