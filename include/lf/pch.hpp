#pragma once
//pch.hpp - precompiled headers for lefaye

//standard library headers
#include <cstdio>
#include <cstdint>
#include <array>

//external apis
#ifdef LF_WIN32
  #define WIN32_LEAN_AND_MEAN
  #include <Windows.h>
#endif

#include <vulkan/vulkan.h>
