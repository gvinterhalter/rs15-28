#define GLEW_STATIC // we need this because we link with glew32s.lib (static)


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fbxsdk.h>

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <chrono>
#include <thread>

#include "nodes/transform.h"
#include "nodes/mesh.h"
#include <unordered_map>

#include "nodes/shdProgram.h"

#include "Scene.h"
#include "Importer.h"

using namespace mfe;

	std::vector<Mesh> meshList;

	static std::vector<Transform *> rootLvl;

	// Shader sources
	static const GLchar* vertexSource =
		"#version 150 core\n"
		"in vec3 position;"
		"in vec3 color;"
		"out vec3 Color;"
		"uniform mat4 MVP;"
		"void main() {"
		"   Color = color;"
		"   gl_Position = MVP * vec4(position, 1.0);"
		"}";
	static const GLchar* fragmentSource =
		"#version 150 core\n"
		"in vec3 Color;"
		"out vec4 outColor;"
		"void main() {"
		"   outColor = vec4(Color, 1.0);"
		"}";

/////////////////////////////////////////////////////////////////////////////////


	int main(int argc, char **argv){
		Scene scn(640, 1024, "Pera");

		{
			Importer imp(scn);
			imp.importScene("../test_resources/vojnik.fbx");
		}

		scn.gameLoop();
		return 0;
	}




//////////////////////////////////////////////////////////////////////////////////////













	int m(int argc, char **argv){
		std::cout << "Hello, this is MATF strike" << std::endl;

		if (glfwInit() == false){
			std::cerr << "Error, can't initialise glfw" << std::endl;
			exit(EXIT_FAILURE);
		}

		glfwWindowHint(GLFW_SAMPLES, 4); // antialiasing 
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

		glfwWindowHint(GLFW_SRGB_CAPABLE, true);


		GLFWwindow * window = glfwCreateWindow(640, 480, "My OPNEGL", NULL, NULL);

		if (!window){
			std::cerr << "Error, can't create window" << std::endl;
			glfwTerminate();
			exit(EXIT_FAILURE);
		}

		glfwMakeContextCurrent(window);

		// glew
		glewExperimental = GL_TRUE;
		glewInit();

		//glEnable(GL_FRAMEBUFFER_SRGB);

		//****************************************************************************

		// Create a Vertex Buffer Object and copy the vertex data to it
		GLuint vao;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		

		GLfloat vertices[] = {
			-0.5f, 0.5f,   0.f,    0.0f, 0.0f, 1.0f, // Top-left
			 0.5f, 0.5f,   0.f,    0.0f, 1.0f, 1.0f, // Top-right
			 0.5f, -0.5f,  0.f,    1.0f, 0.0f, 1.0f, // Bottom-right

			 0.5f, -0.5f,  0.f,    1.0f, 0.0f, 1.0f, // Bottom-right
			-0.5f, 0.5f,   0.f,    0.0f, 0.0f, 1.0f, // Top-left
			-0.5f, -0.5f,   0.f,    1.0f, 0.0f, 0.0f, // Bottom-left
		};



		GLuint vbo;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


		auto * vrtxShd = new Shader("vrtx", vertexSource, Shader::VERTEX);
		auto * fragShd = new Shader("frag", fragmentSource, Shader::FRAGMENT);
		ShdProgram shdProg(vrtxShd, fragShd, "outColor");
		shdProg.useProgram();


		// Specify the layout of the vertex data
		GLint posAttrib = glGetAttribLocation(shdProg.program(), "position");
		glEnableVertexAttribArray(posAttrib);
		glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0 );

		GLint colAttrib = glGetAttribLocation(shdProg.program(), "color");
		glEnableVertexAttribArray(colAttrib);
		glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)) );

		/* MATRIX MATRIX MATRIX MATRIX MATRIX  MATRIX MATRIX MATRIX MATRIX MATRIX */
			// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
			glm::mat4 Projection = glm::perspective(45.0f, 640.f / 480.f, 0.1f, 100.0f);
			// Camera matrix
			glm::mat4 View = glm::lookAt(
				glm::vec3(4, 3, 3), // Camera is at (4,3,3), in World Space
				glm::vec3(0, 0, 0), // and looks at the origin
				glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
				);
			// Model matrix : an identity matrix (model will be at the origin)
			glm::mat4 Model = glm::mat4(1.0f);  // Changes for each model !
			// Our ModelViewProjection : multiplication of our 3 matrices
			glm::mat4 MVP = Projection * View * Model; // Remember, matrix multiplication is the other way around
		/* MATRIX MATRIX MATRIX MATRIX MATRIX  MATRIX MATRIX MATRIX MATRIX MATRIX */

			GLint MatrixID = glGetUniformLocation(shdProg.program(), "MVP");
			glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

		// event loop
		while (!glfwWindowShouldClose(window)){

			glClearColor(0, 0, 0, 1);
			glClear(GL_COLOR_BUFFER_BIT);


			Model = glm::rotate(Model, glm::radians(5.f), glm::vec3(0., 1., 0.));
			MVP = Projection * View * Model;
			glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
			// Draw a rectangle from the 2 triangles using 6 indices
			//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glDrawArrays(GL_TRIANGLES, 0, 6);

			glfwSwapBuffers(window);

			glfwPollEvents();


			// ESC, for full screen windows
			if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
				glfwSetWindowShouldClose(window, GL_TRUE);

			std::this_thread::sleep_for(std::chrono::milliseconds(30));
		}


		return 0;
	}



