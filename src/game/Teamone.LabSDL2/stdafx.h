// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <iostream>
#include <vector>
#include <memory>

// TODO: reference additional headers your program requires here
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <Eigen/Dense>
#include <Eigen/Geometry>

#define safe_delete(obj) if(obj != nullptr) { delete obj; obj = nullptr; }

#ifndef NDEBUG
#define debug_print(msg) { std::cout << __FILE__ << ":" << __LINE__ << " " << msg << std::endl; }
#else
#define debug_print(msg) { void(0); }
#endif