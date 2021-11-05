#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include "renderer.h"
using namespace std;

namespace aie 
{
	shader loadShader(const char* vertPath, const char* fragPath);

	string readShader(const char* path);
}
