#pragma once
#define GLEW_STATIC // we need this because we link with glew32s.lib (static)

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <iostream>
#include <fstream>
#include <cstring>
#include <memory>
#include <iostream>

#include "Exception.h"

namespace mfe{

	class Shader
	{
	public:
		enum ShaderType {VERTEX, FRAGMENT};

		~Shader() { delete m_src; glDeleteShader(m_shd); }

		Shader(const char * name, const char * src, ShaderType t) 
			: m_src(_strdup(src)), m_name(_strdup(name)),  m_type(t)
		{ 
			compile(); 
		}

		Shader(const char * name, std::ifstream file, ShaderType t) // namerno ne prosledjujemo po referenci, RAII
			: m_name(_strdup(name)), m_type(t) 
		{ 
			if (file.is_open() == false){
				std::cerr << "Error, shader file is not opend" << std::endl;
				exit(EXIT_FAILURE);
			}

			// citamo iz fajla na komplikovan nacin :)
			std::string str((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
			m_src = _strdup(str.c_str());

			compile();
		}

		// brisemo copy, copy-asign, move i move-asign
		Shader(const Shader &)             = delete;
		Shader & operator=(const Shader &) = delete;
		Shader(Shader &&)                  = delete;
		Shader & operator=(Shader &&)      = delete;

		void compile() {
			switch (m_type){
			case ShaderType::VERTEX:
				m_shd = glCreateShader(GL_VERTEX_SHADER);
				break;
			case ShaderType::FRAGMENT:
				m_shd = glCreateShader(GL_FRAGMENT_SHADER);
				break;
			}

			glShaderSource(m_shd, 1, &m_src, NULL);
			glCompileShader(m_shd);
			statusReport();
		}


		GLuint shd() { return m_shd; }

	protected:
		ShaderType m_type;
		char * m_src;
		char * m_name;
		GLuint m_shd;
		GLint m_compileStatus;

		void statusReport(){
			GLint status;
			glGetShaderiv(m_shd, GL_COMPILE_STATUS, &status);

			std::cout << "Shader " << m_name << ": "; 
			if (status == GL_TRUE){
				std::cout << " compilation SUCCESS" << std::endl;
				return;
			}
			// else print log error and throw exception

			char infoLog[1024];
			glGetShaderInfoLog(m_shd, 1024, NULL, infoLog);
			std::cerr << std::endl  << infoLog << std::endl;
			throw GlslCompileErr();
		}

	};

	class ShdProgram
	{
	public:
		~ShdProgram(){ glDeleteProgram(m_shdProgram); }
		ShdProgram(Shader * vShd, Shader * fShd, const char *out = "outColor")
			: m_vrtxShd(vShd), m_fragShd(fShd)
		{
			m_shdProgram = glCreateProgram();
			glAttachShader(m_shdProgram, m_vrtxShd->shd() );
			glAttachShader(m_shdProgram, m_fragShd->shd());
			glBindFragDataLocation(m_shdProgram, 0, out);
			linkProgram();
		}

		void linkProgram() {
			glLinkProgram(m_shdProgram); 

			GLint status;
			glGetProgramiv(m_shdProgram, GL_LINK_STATUS, &status);
			if (status == GL_TRUE)
				return;
			// else print log error and throw exception

			char infoLog[1024];
			glGetProgramInfoLog(m_shdProgram, 1024, NULL, infoLog);
			std::cerr << "Link Faild: "  << infoLog << std::endl;
			throw GlslLinkErr();
		}

		void useProgram() {glUseProgram(m_shdProgram); }
		GLuint program() { return m_shdProgram; }

	private:
		std::shared_ptr<Shader> m_vrtxShd;
		std::shared_ptr<Shader> m_fragShd;
		GLuint m_shdProgram;

	};

}