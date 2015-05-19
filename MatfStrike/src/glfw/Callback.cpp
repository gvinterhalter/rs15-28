#include "glfw/Callback.h"

#include <GLFW/glfw3.h>
#include <iostream>
#include <mutex>

void debugKeyboard(int key, int scancode, int action, int mods){
	// ako nekim cudom ikad budem debagovao dve tastature koje kontrolisu dva
	// Window prozora onda bi cout trebalo zakljucati... :D
	static std::mutex coutMutex;
	std::unique_lock<std::mutex> lock(coutMutex);

	std::cout << (char)key << " " << (int)key << " ";
	std::cout << (
		action == GLFW_PRESS ? "press" :
		action == GLFW_RELEASE ? "release" :
		action == GLFW_REPEAT ? "repeat" : "unknown_action")
		<< " ";
	if (mods & GLFW_MOD_SHIFT)
		std::cout << "SHIFT ";
	if (mods & GLFW_MOD_CONTROL)
		std::cout << "CONTROL ";
	if (mods & GLFW_MOD_ALT)
		std::cout << "ALT ";
	if (mods & GLFW_MOD_SUPER)
		std::cout << "SUPER ";
	std::cout << std::endl;
}
