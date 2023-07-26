#pragma once

#include "ppch.h"

#define ASSERT(x, ...) { if(!(x)) { std::cout<< "[Error] Assertion failed: " << __VA_ARGS__ << std::endl; __debugbreak(); } }
#define LOG(...) { std::cout<< "[INFO] " << __VA_ARGS__ << std::endl; }