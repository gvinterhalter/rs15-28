#pragma once
#include "node.h"
#include <string>

namespace mfe{

	class ShdProgram : public Node
	{
	public:
		ShdProgram(std::string name, Node * parent);
	};


}