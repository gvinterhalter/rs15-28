#pragma once
#define GLEW_STATIC // we need this because we link with glew32s.lib (static)

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>

#include "nodes/Shader.h"
#include "nodes/mesh.h"
#include "PerspectiveCamera.h"

namespace mfe{


	class ShdProgram
	{
	public:
		~ShdProgram();
		ShdProgram(Shader * vShd, Shader * fShd, const char *out = "outColor");
		

		void linkProgram();
		void addMesh(Mesh *mesh);
		const std::vector<Mesh *> & meshList() { return m_meshList; }

		void useProgram() {glUseProgram(m_shdProgram); }
		GLuint program() { return m_shdProgram; }

	private:
		std::shared_ptr<Shader> m_vrtxShd;
		std::shared_ptr<Shader> m_fragShd;
		GLuint m_shdProgram;

		std::vector<Mesh *> m_meshList;

	};

}