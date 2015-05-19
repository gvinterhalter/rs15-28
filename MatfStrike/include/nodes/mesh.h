#pragma once
#define GLEW_STATIC // we need this because we link with glew32s.lib (static)

#include <fbxsdk.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "PerspectiveCamera.h"

namespace mfe{

	class Mesh
	{
	public:
		Mesh(GLfloat * data, GLuint size);
		void draw();

		void connectShadingProgram(GLuint shd);
		void rotateY(float);

	private:
		GLuint m_vbo; // vertex buffer object
		GLuint m_vao; // vertex array object
		glm::mat4 m_transform = glm::mat4(1);

		GLuint m_transformIndex;

		GLfloat* m_data;
		GLuint m_data_size;
	};

}
