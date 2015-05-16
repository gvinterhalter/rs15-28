#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>	
#include <glm/gtc/type_ptr.hpp>	

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include "nodes/shdProgram.h"
#include "nodes/mesh.h"
#include "PerspectiveCamera.h"
#include "Exception.h"


namespace mfe{

	class Scene
	{
	public:
		Scene(int w, int h, const  std::string & t);
		~Scene();

		void initializeGraphics();
		void gameLoop();
		void buildDefaultShaders();

		void addMesh(GLfloat * buff, GLuint size);
		//void addMaterial(); // TODO
		//void addLight();    // TODO

	private:
		// Window
		GLFWwindow * m_window;
		unsigned int m_windowWidth = 640;
		unsigned int m_windowHeight = 480;
		std::string m_windowTittle = "Test Game";

		PerspectiveCamera m_camera;

		Shader * m_vrtxShader;
		Shader * m_fragShader;
		ShdProgram * m_shdProgram;

		std::vector<Mesh> m_meshList;
	};

}
