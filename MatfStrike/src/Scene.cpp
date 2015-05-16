#include "Scene.h"

namespace mfe{

	Scene::Scene(int w, int h, const  std::string & t)
		: m_windowWidth(w), m_windowHeight(h), m_windowTittle(t), m_camera(w, h)
	{
		initializeGraphics();
	}

	Scene::~Scene() { }


	void Scene::initializeGraphics(){
		// glfw
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
		
		glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);
		glfwWindowHint(GLFW_SRGB_CAPABLE, true);

		m_window = glfwCreateWindow(m_windowWidth, m_windowHeight, m_windowTittle.c_str(), NULL, NULL);

		if (!m_window){
			std::cerr << "Error, can't create window" << std::endl;
			glfwTerminate();
			exit(EXIT_FAILURE);
		}

		glfwMakeContextCurrent(m_window);

		// glew
		glewExperimental = GL_TRUE;
		glewInit();

		// opengl
		glClearColor(0, 0, 0, 1);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_DEPTH_BUFFER_BIT);
		//glEnable(GL_CULL_FACE);

		buildDefaultShaders();
	}

	void Scene::gameLoop(){
		while (!glfwWindowShouldClose(m_window)){
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			for (auto & x : m_meshList){
				x.rotateY(2.f);
				x.draw();
			}

			glfwSwapBuffers(m_window);
			glfwPollEvents();

			// ESC, for full screen windows
			if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
				glfwSetWindowShouldClose(m_window, GL_TRUE);

		}
	}

	void Scene::buildDefaultShaders(){
		try {
			m_vrtxShader = new Shader("test.vert", std::ifstream("../glsl/test.vert"), Shader::VERTEX);
			m_fragShader = new Shader("normals.frag", std::ifstream("../glsl/normals.frag"), Shader::FRAGMENT);
			m_shdProgram = new  ShdProgram(m_vrtxShader, m_fragShader, "outColor");
		}
		catch (Exception & e){
			exit(EXIT_FAILURE);
		}
	}

	void Scene::addMesh(GLfloat * buff, GLuint size){
		m_meshList.emplace_back(Mesh(buff, size, m_shdProgram, m_camera));
	}

}