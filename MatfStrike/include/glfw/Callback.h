#pragma once

// pointeri na funkcije koje koriste staticke funkcije
typedef void(*keyCallback) (int key, int scancode, int action, int mods);
typedef void(*cursorCallback) (double xPos, double yPos);
typedef void(*mouseBtnCallback) (int button, int action, int mods);
typedef void(*scrollCallback) (double xOffset, double yOffset);

void debugKeyboard(int key, int scancode, int action, int mods);
