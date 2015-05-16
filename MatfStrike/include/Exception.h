#pragma once

#include <exception>

namespace mfe{

	struct Exception :  public std::exception
	{
		const char * what() const throw () {
			return "mfe base Exception";
		}
	};

	struct GlslCompileErr : Exception
	{
		const char * what() const throw(){
			return "glsl compile error";
		}

	};

	struct GlslLinkErr : Exception
	{
		const char * what() const throw(){
			return "glsl link error";
		}

	};

}