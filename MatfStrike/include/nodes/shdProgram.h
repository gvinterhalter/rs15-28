#pragma once
#define GLEW_STATIC // we need this because we link with glew32s.lib (static)

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <memory>

#include "nodes/mesh.h"

namespace mfe{

	class Shader;
	class PerspectiveCamera;

	class ShdProgram
	{
	public:
		~ShdProgram();
		ShdProgram(Shader * vShd, Shader * fShd, const char *out = "outColor");
		

		void linkProgram();
		void useProgram();
		GLuint program();

		const std::vector<Mesh *> & meshList();
		void addMesh(Mesh *mesh);

	private:
		std::shared_ptr<Shader> m_vrtxShd;
		std::shared_ptr<Shader> m_fragShd;
		GLuint m_shdProgram;

		std::vector<Mesh *> m_meshList;

	};

}