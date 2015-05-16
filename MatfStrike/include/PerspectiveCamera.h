#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>	
#include <glm/gtc/type_ptr.hpp>	

namespace mfe{


	class PerspectiveCamera
	{
	public:
		PerspectiveCamera(int w, int h, float fov = 45.0f, float near = 0.1f, float far = 1000.0f);

		glm::mat4 projection;
		glm::mat4 view;
		glm::mat4 PV;
	private:

		glm::vec3 m_pos = glm::vec3(0, 0, 1);
		glm::vec3 m_target = glm::vec3(0, 0, 0);
		glm::vec3 m_upVector = glm::vec3(0, 1, 0);
	};


}
