#include "PerspectiveCamera.h"

namespace mfe{

		PerspectiveCamera::PerspectiveCamera(int w, int h, float fov, float near, float far){
			projection = glm::perspective(fov, (float)w / h, near, far);
			//m_view = glm::lookAt(m_pos, m_target, m_upVector);
			view = glm::lookAt(
				glm::vec3(0, 0.5, 1), // Camera is in World Space
				glm::vec3(0, 0.5, 0), // and looks at the origin
				glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
				);
			PV = projection * view;
		}
}
