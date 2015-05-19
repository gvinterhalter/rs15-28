#pragma once

#include <glm/glm.hpp>

namespace mfe{

	class PerspectiveCamera 
	{
	public:
		PerspectiveCamera(int w, int h, float fov = 45.0f, float near = 0.1f, float far = 1000.0f);

		void calcTransform();
		void calcProjection(float fov, float near, float far);
		void changeResolution(int w, int h);

		void keyCallback(int key, int scancode, int action, int mods);
		void cursorPos_callback(double xPos, double yPos);

		glm::mat4 projection;
		glm::mat4 view;
		glm::mat4 PV;

	private:
		int m_width;
		int m_height;


		double m_oldX = 0;
		double m_oldY = 0;

		glm::vec3 m_pos = glm::vec3(0, 0.5, 1);
		glm::vec3 m_target = glm::vec3(0, 0.5, 0);
		glm::vec3 m_upVector = glm::vec3(0, 1, 0);

	};


}
