#pragma once

#include "node.h"
#include <fbxsdk.h>
#include <GLFW/glfw3.h>

namespace mfe{

	class Mesh : public Node
	{
	public:
		Mesh(const std::string name, Node * parent) : Node(name, parent) {}

	private:
		// vertex data
	};

}
