#include"Model.h"

const unsigned int width = 1920;
const unsigned int height = 1080;

int main()
{

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, "YoutubeOpenGL", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	gladLoadGL();

	glViewport(0, 0, width, height);

	Shader shaderProgram("default.vert", "default.frag");

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(1.0f, 1.5f, 1.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	shaderProgram.Activate();
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

	glEnable(GL_DEPTH_TEST);

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	std::string modelBeePath = "models/Bee/bee.gltf";
	std::string modelFlowerPath = "models/Flower/flower.gltf";
	std::string modelHivePath = "models/Hive/hive.gltf";
	
	Model modelBee(modelBeePath.c_str());
	Model modelFlower(modelFlowerPath.c_str());
	Model modelHive(modelHivePath.c_str());

	glm::vec3 beeTrajectory = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::quat beeRotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
	
	float XDegrees = 0.0f, YDegrees = 5.0f, ZDegrees = 5.0f;
	beeRotation = glm::rotate(beeRotation, XDegrees, glm::vec3(1.0f, 0.0f, 0.0f));		//X
	beeRotation = glm::rotate(beeRotation, YDegrees, glm::vec3(0.0f, 1.0f, 0.0f));		//Y
	beeRotation = glm::rotate(beeRotation, ZDegrees, glm::vec3(0.0f, 0.0f, 1.0f));		//Z

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.Inputs(window);

		camera.updateMatrix(45.0f, 0.1f, 100.0f);

		modelBee.Draw(shaderProgram, camera, beeTrajectory, beeRotation, glm::vec3(0.25f,0.25f,0.25f));
		modelFlower.Draw(shaderProgram, camera,glm::vec3(30.0f, 30.0f, 0.0f));
		modelHive.Draw(shaderProgram, camera);

		beeTrajectory[0] += 0.01f;
		beeTrajectory[1] -= 0.001f;
		beeTrajectory[2] -= 0.005f;

		/*if (ZDegrees > 0.02f) {
			ZDegrees -= 0.02f;
			ZDegrees += 0.0001f;
		}
		else {
			ZDegrees += 0.0001f;
		}*/
		
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	shaderProgram.Delete();

	glfwDestroyWindow(window);

	glfwTerminate();
	return 0;
}