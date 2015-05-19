#include "Scene.h"


namespace mfe{


	Scene::Scene(int w, int h, const  std::string & t)
		: m_windowWidth(w), m_windowHeight(h), m_windowTittle(t), m_camera(w, h)
	{
		initializeGraphics(NULL);
		gloabl_camera = & m_camera;
	}

	Scene::Scene(const std::string & t)
		: m_windowTittle(t), m_camera(640, 480)
	{

		auto * monitor = glfwGetPrimaryMonitor();
		auto * mode = glfwGetVideoMode(monitor);
		m_camera = PerspectiveCamera(mode->width, mode->height);

		initializeGraphics(monitor);
		gloabl_camera = & m_camera;
	}

	Scene::~Scene() { }


	void Scene::initializeGraphics(GLFWmonitor * monitor){
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

		m_window = glfwCreateWindow(m_windowWidth, m_windowHeight, m_windowTittle.c_str(),
			monitor, NULL);

		if (!m_window){
			std::cerr << "Error, can't create window" << std::endl;
			glfwTerminate();
			exit(EXIT_FAILURE);
		}

		glfwMakeContextCurrent(m_window);

		// set callbacks for mouse and keyboard
		glfwSetKeyCallback(m_window, key_callback);
		glfwSetMouseButtonCallback(m_window, mouseBtn_callback);
		glfwSetScrollCallback(m_window, scroll_callback);
		glfwSetCursorPosCallback(m_window, cursorPos_callback);

		glfwSetCursorPos(m_window,  m_windowWidth / 2, m_windowHeight / 2);
		glfwSetCursor( m_window, glfwCreateStandardCursor(GLFW_CROSSHAIR_CURSOR) );

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


			// Update Camera movment
			GLint attrPos;
			m_camera.calcTransform();
			attrPos = glGetUniformLocation(m_shdProgram->program(), "projectionMatrix");
			glUniformMatrix4fv(attrPos, 1, GL_FALSE, &m_camera.projection[0][0]);
			attrPos = glGetUniformLocation(m_shdProgram->program(), "viewMatrix");
			glUniformMatrix4fv(attrPos, 1, GL_FALSE, &m_camera.view[0][0]);

			m_shdProgram->useProgram();
			// render meshes in shaderProgram
			for (auto * x : m_shdProgram->meshList()){
				x->rotateY(4.f);
				x->draw();
			}

			glfwSwapBuffers(m_window);
			glfwPollEvents();

			std::this_thread::sleep_for(std::chrono::milliseconds(1000/30));

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

	void Scene::addMesh(Mesh * mesh){
		m_meshList.push_back(mesh);
		m_shdProgram->addMesh(mesh);
	}




}
