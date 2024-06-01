#include <map>
#include "Input.h"
#include <iostream>

namespace GGL
{
	void Input::FlushKeys() {
		for(const auto &pair : keys) {
			keys.at(pair.first) = false;
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

	std::map<int, bool> Input::keys = {
		{ 0x30, false },
		{ 0x31, false },
		{ 0x32, false },
		{ 0x33, false },
		{ 0x34, false },
		{ 0x35, false },
		{ 0x36, false },
		{ 0x37, false },
		{ 0x38, false },
		{ 0x39, false },
		{ 0x41, false },
		{ 0x42, false },
		{ 0x43, false },
		{ 0x44, false },
		{ 0x45, false },
		{ 0x46, false },
		{ 0x47, false },
		{ 0x48, false },
		{ 0x49, false },
		{ 0x4A, false },
		{ 0x4B, false },
		{ 0x4C, false },
		{ 0x4D, false },
		{ 0x4E, false },
		{ 0x4F, false },
		{ 0x50, false },
		{ 0x51, false },
		{ 0x52, false },
		{ 0x53, false },
		{ 0x54, false },
		{ 0x55, false },
		{ 0x56, false },
		{ 0x57, false },
		{ 0x58, false },
		{ 0x59, false },
		{ 0x5A, false },
	};
}