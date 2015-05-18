#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>	
#include <glm/gtc/type_ptr.hpp>	

#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include <string>
#include <iostream>
#include "Scene.h"

namespace mfe{

	class Window
	{
	public:
		Window(const std::string & title, int w = 800, int h = 600, bool fullScreen = 0);

		void glfwLoop();
		void addScene(Scene * scene) { m_scene = scene; }
		void show();

	private:
		std::string m_title;
		unsigned int m_width;
		unsigned int m_height;

		GLFWmonitor * m_monitor; // if not null it is used for full screen mode (glfw works this way)
		GLFWwindow * m_window;

		Scene * m_scene;

		void setOpenGL();
		void setCallbacks();

	};

}
