#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>	
#include <glm/gtc/type_ptr.hpp>	

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>

#include "nodes/shdProgram.h"
#include "nodes/mesh.h"
#include "PerspectiveCamera.h"
#include "Exception.h"


namespace mfe{

	static PerspectiveCamera * gloabl_camera;


	class Scene
	{
	public:
		Scene();
		Scene(int w, int h, const  std::string & t);
		Scene(const std::string & t);
		~Scene();

		void initializeGraphics(GLFWmonitor * mode);
		void gameLoop();
		void buildDefaultShaders();

		void addMesh(GLfloat * buff, GLuint size);
		//void addMaterial(); // TODO
		//void addLight();    // TODO

	private:
		// Window
		GLFWmonitor * m_monitor;
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





	static void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods){

//#define _DEGUB_KEY_CALLBACK_ 
#ifdef _DEGUB_KEY_CALLBACK_
		std::cout << (char)key << " " << (int)key << " ";
		std::cout << (
			action == GLFW_PRESS ? "press" :
			action == GLFW_RELEASE ? "release" :
			action == GLFW_REPEAT ? "repeat" : "unknown_action")
			<< " ";
		if (mods & GLFW_MOD_SHIFT)
			std::cout << "SHIFT ";
		if (mods & GLFW_MOD_CONTROL)
			std::cout << "CONTROL ";
		if (mods & GLFW_MOD_ALT)
			std::cout << "ALT ";
		if (mods & GLFW_MOD_SUPER)
			std::cout << "SUPER ";
		std::cout << std::endl;
#endif // _DEGUB_KEY_CALLBACK_

		gloabl_camera->keyCallback(key, scancode, action, mods);

	}



	static void	cursorPos_callback(GLFWwindow * window, double xPos, double yPos){
		gloabl_camera->cursorPos_callback(xPos, yPos);

	}

	static void	mouseBtn_callback(GLFWwindow * window, int button, int action, int mods){

	}

	static void	scroll_callback(GLFWwindow * window, double xOffse, double yOffset){

	}





}
