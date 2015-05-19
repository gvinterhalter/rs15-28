#pragma once
#define GLEW_STATIC // we need this because we link with glew32s.lib (static)

#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include <string>
#include <memory>

namespace mfe{

	class Shader
	{
	public:
		enum ShaderType {VERTEX, FRAGMENT};

		~Shader();
		Shader(const char * name, const char * src, ShaderType t);
		Shader(const char * name, std::ifstream file, ShaderType t);// namerno ne prosledjujemo po referenci, RAII

		// brisemo copy, copy-asign, move i move-asign
		Shader(const Shader &)             = delete;
		Shader & operator=(const Shader &) = delete;
		Shader(Shader &&)                  = delete;
		Shader & operator=(Shader &&)      = delete;

		void compile();
		GLuint shd() { return m_shd; }

	private:
		ShaderType m_type;
		char * m_src;
		char * m_name;
		GLuint m_shd;
		GLint m_compileStatus;

		void statusReport();
	};

}
