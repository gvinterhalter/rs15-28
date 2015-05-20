#pragma once
#define GLEW_STATIC // jer staticki linkujemo  glew

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <vector>
#include <iostream>

#include "Exception.h"
#include "PerspectiveCamera.h" // za sad jer ne cuvam poiner na kameru


namespace mfe{

	class Mesh;
	class Shader;
	class ShdProgram;

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

		void addMesh(Mesh * mesh);
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

		std::vector<Mesh *> m_meshList;


	};


	static void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods);
	static void	cursorPos_callback(GLFWwindow * window, double xPos, double yPos);
	static void	mouseBtn_callback(GLFWwindow * window, int button, int action, int mods);
	static void	scroll_callback(GLFWwindow * window, double xOffse, double yOffset);








}
