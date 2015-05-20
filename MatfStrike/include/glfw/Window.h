#pragma once
#define GLEW_STATIC // jer staticki linkujemo  glew

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>	
#include <glm/gtc/type_ptr.hpp>	

#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include <unordered_map>
#include <string>
#include <iostream>

#include "glfw/Callback.h"

namespace mfe{

	class Window
	{
	public:
		Window(const std::string & title, int w = 800, int h = 600, bool fullScreen = 0);

		void glfwLoop();
		void registerCallbacks(keyCallback k, cursorCallback c, mouseBtnCallback mb, scrollCallback s);


	private:
		std::string m_title;
		unsigned int m_width;
		unsigned int m_height;

		GLFWmonitor * m_monitor; // if not null it is used for full screen mode (glfw works this way)
		GLFWwindow * m_window;

		// ovaj tip funkcija je definisan u CallbackTypes.h
		keyCallback m_kFunc;
		cursorCallback m_cFunc;
		mouseBtnCallback m_mbFunc;
		scrollCallback m_sFunc;

		static std::unordered_map<GLFWwindow *, Window *> allWindows; // used in callback functions below

		// Staticke funkcije koje cu registrovati registerCallback metod klase Window
		static void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods){ allWindows[window]->m_kFunc(key, scancode, action, mods); }
		static void	cursor_callback(GLFWwindow * window, double xPos, double yPos){ allWindows[window]->m_cFunc(xPos, yPos); }
		static void	mouseBtn_callback(GLFWwindow * window, int button, int action, int mods){ allWindows[window]->m_mbFunc(button, action, mods); }
		static void	scroll_callback(GLFWwindow * window, double xOffset, double yOffset){ allWindows[window]->m_sFunc(xOffset, yOffset); }
	};

	


}
