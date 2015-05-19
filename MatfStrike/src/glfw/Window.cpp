#include "glfw/Window.h"

namespace mfe{

	Window::Window(const std::string & title, int w, int h, bool fullScreen)
		: m_title(title), m_width(w), m_height(h)
	{
		if (glfwInit() == false)
			std::cerr << "Fatal Error, can't initialise glfw" << std::endl, exit(EXIT_FAILURE);

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);

		glfwWindowHint(GLFW_SAMPLES, 4); // antialiasing 
		glfwWindowHint(GLFW_RESIZABLE, false);
		
		glfwWindowHint(GLFW_DOUBLEBUFFER, true);
		glfwWindowHint(GLFW_SRGB_CAPABLE, false);

		m_monitor = fullScreen ? glfwGetPrimaryMonitor() : NULL;

		// creating window
		m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), m_monitor, NULL);
		if (!m_window)
			std::cerr << "Fatal Error, can't create a window" << std::endl, glfwTerminate(), exit(EXIT_FAILURE);

		allWindows[m_window] = this; // used for callbacks

		// set cursor on the center of the screen and chage shape
		// glfwSetCursorPos(m_window,  m_width / 2, m_height / 2);
		// glfwSetCursor( m_window, glfwCreateStandardCursor(GLFW_CROSSHAIR_CURSOR) );

		// glew 
		// NE ZNAM gde da stavim ovo ?
		glewExperimental = true;
		glewInit();
	}

	void Window::show(){
		glfwMakeContextCurrent(m_window); // now we can use opengl 
		setOpenGL();
	}

	void Window::setOpenGL(){
		glClearColor(0, 0, 0, 1);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_DEPTH_BUFFER_BIT);
		//glEnable(GL_CULL_FACE);
	}

	void Window::setCallbacks(){
		// set callbacks for mouse and keyboard
		//glfwSetKeyCallback(m_window, key_callback);
		//glfwSetMouseButtonCallback(m_window, mouseBtn_callback);
		//glfwSetScrollCallback(m_window, scroll_callback);
		//glfwSetCursorPosCallback(m_window, cursorPos_callback);
	}

	void Window::glfwLoop(){
		while (!glfwWindowShouldClose(m_window)){

			//m_scene->render();

			glfwSwapBuffers(m_window);
			glfwPollEvents();


			// ESC, for full screen windows
			if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
				glfwSetWindowShouldClose(m_window, GL_TRUE);

		}
	}

	// !!!! primeti da glfw registruje staticke funkcije, ne one koje su prosledjene
	// kao argumenti. Prosledjene mi govore sta smem da registrujem da ne bi referisao 
	// u statickim funkcijama nest sto ne postoji
	void Window::registerCallbacks(keyCallback k, cursorCallback c, mouseBtnCallback mb, scrollCallback s){
		if (k) // keyboard
			m_kFunc = k, glfwSetKeyCallback(m_window, key_callback);
		if (c) // cursor
			m_cFunc = c, glfwSetCursorPosCallback(m_window, cursor_callback);
		if (mb) // mouse btn
			m_mbFunc = mb, glfwSetMouseButtonCallback(m_window, mouseBtn_callback);
		if (s) // scroll
			m_sFunc = s, glfwSetScrollCallback(m_window, scroll_callback);
	}

}
