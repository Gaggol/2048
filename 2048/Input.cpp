#include <map>
#include "Input.h"

using namespace GGL;

void Input::FlushKeys() {
	for(int i = 0; i < keys.size(); i++) {
		keys[i] = false;
	}
}

bool Input::GetKeyDown(int id) {
	return keys[id];
}
bool Input::GetKeyUp(int id) {
	return keys[id];
}
void Input::SetKeyDown(int id) {
	keys[id] = true;
}
void Input::SetKeyUp(int id) {
	keys[id] = false;
}