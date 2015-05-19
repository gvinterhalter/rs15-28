#include "nodes/Shader.h"

#include <iostream>
#include <fstream>
#include <iostream>

#include "Exception.h"

namespace mfe{

		Shader::~Shader()
		{
			delete m_src; glDeleteShader(m_shd); 
		}

		Shader::Shader(const char * name, const char * src, ShaderType t) 
			: m_src(_strdup(src)), m_name(_strdup(name)),  m_type(t)
		{ 
			compile(); 
		}

		Shader::Shader(const char * name, std::ifstream file, ShaderType t) // namerno ne prosledjujemo po referenci, RAII
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

		void Shader::compile() {
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


		// private
		void Shader::statusReport(){
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

}
