#include "nodes/mesh.h"

#include <fbxsdk.h>
#include <glm/gtc/matrix_transform.hpp>	
#include <glm/gtc/type_ptr.hpp>	

namespace mfe{

	Mesh::Mesh(GLfloat * data, unsigned int size) 
		: m_data(data), m_data_size(size) 
	{
		glGenVertexArrays(1, &m_vao);
		glBindVertexArray(m_vao);

		glGenBuffers(1, &m_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, m_data_size*sizeof(GLfloat), m_data, GL_STATIC_DRAW);
	}

	void Mesh::connectShadingProgram(GLuint shd){
		GLuint attrPos;
		attrPos = glGetAttribLocation(shd, "P");
		glVertexAttribPointer(attrPos, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
		glEnableVertexAttribArray(attrPos);
		
		attrPos = glGetAttribLocation(shd, "N");
		glVertexAttribPointer(attrPos, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(attrPos);

		attrPos = glGetAttribLocation(shd, "uv");
		glVertexAttribPointer(attrPos, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(attrPos);

		glUseProgram(shd);

		attrPos = glGetUniformLocation(shd, "modelMatrix");
		m_transformIndex = attrPos;
		glUniformMatrix4fv(m_transformIndex, 1, GL_FALSE, & m_transform[0][0]);
	}

	void Mesh::draw(){
		glBindVertexArray(m_vao);
		glDrawArrays(GL_TRIANGLES, 0, m_data_size);
	}

	void Mesh::rotateY(float r){
		m_transform = glm::rotate(m_transform, glm::radians(r), glm::vec3(0., 1., 0.));
		glUniformMatrix4fv(m_transformIndex, 1, GL_FALSE, & m_transform[0][0]);
	}
}
