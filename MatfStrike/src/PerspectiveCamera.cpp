#include "PerspectiveCamera.h"

#include <glm/gtc/matrix_transform.hpp>	
#include <glm/gtc/type_ptr.hpp>	
#include <GLFW/glfw3.h>

#include <iostream>

namespace mfe{

		PerspectiveCamera::PerspectiveCamera(int w, int h, float fov, float near, float far)
			: m_width(w), m_height(h)
		{
			projection = glm::perspective(fov, (float)w / h, near, far);
			view = glm::lookAt(m_pos, m_target, m_upVector);
			PV = projection * view;
		}

		void PerspectiveCamera::calcTransform(){
			view = glm::lookAt(m_pos, m_target, m_upVector);
			PV = projection * view;
		}

		void PerspectiveCamera::calcProjection(float fov, float near, float far){
			projection = glm::perspective(fov, (float)m_width / m_height, near, far);
		}

		void PerspectiveCamera::changeResolution(int w, int h){
			m_width = w;
			m_height = h;
		}


		void PerspectiveCamera::keyCallback(int key, int scancode, int action, int mods){

			glm::vec3 move;
			glm::vec3 eyeVec  = glm::normalize(m_target - m_pos);
			glm::vec3 rightVec = glm::normalize(glm::cross(eyeVec, glm::vec3(0.,1.,0.)));
			glm::vec3 upVec = glm::normalize(glm::cross(rightVec, eyeVec));

			switch (key){
			case 'W':  move = eyeVec; break;
			case 'S':  move = -eyeVec; break;
			case 'D':  move = rightVec; break;
			case 'A':  move = -rightVec; break;
			case GLFW_KEY_SPACE:  move = upVec; break;
			case GLFW_KEY_LEFT_ALT:  move = -upVec; break;
			}


			move /= 30;
			// calculate new position
			m_pos += move;
			m_target += move;
		}

		void PerspectiveCamera::cursorPos_callback(double xPos, double yPos){
			//center the cordinate system first
			yPos -= m_height / 2;
			xPos -= m_width / 2;


			glm::vec3 eyeVec  = glm::normalize(m_target - m_pos);
			glm::vec3 rightVec = glm::normalize(glm::cross(eyeVec, glm::vec3(0.,1.,0.)));
			glm::vec3 upVec = glm::normalize(glm::cross(rightVec, eyeVec));

			rightVec *= (xPos - m_oldX) / 100;
			upVec *= -(yPos - m_oldY) / 100;

			m_target += rightVec + upVec;

			m_oldX = xPos;
			m_oldY = yPos;
		}
}
