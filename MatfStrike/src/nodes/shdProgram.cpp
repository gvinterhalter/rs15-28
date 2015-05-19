#include <nodes/ShdProgram.h>

#include <iostream>

namespace mfe{

		ShdProgram::~ShdProgram()
		{ 
			glDeleteProgram(m_shdProgram); 
		}

		ShdProgram::ShdProgram(Shader * vShd, Shader * fShd, const char *out)
			: m_vrtxShd(vShd), m_fragShd(fShd)
		{
			m_shdProgram = glCreateProgram();
			glAttachShader(m_shdProgram, m_vrtxShd->shd() );
			glAttachShader(m_shdProgram, m_fragShd->shd());
			glBindFragDataLocation(m_shdProgram, 0, out);
			linkProgram();
		}

		void ShdProgram::linkProgram() {
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


		void ShdProgram::addMesh(Mesh *mesh){
			m_meshList.push_back(mesh);
			mesh->connectShadingProgram(m_shdProgram);
		}

}