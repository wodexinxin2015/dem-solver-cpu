/************************************************************************************
DEM-Solver-CPU
Dsicrete Element Method Program for landsldies, debris flows and other geohazards
--parallelized and optimized for SMP (Symmetric multiprocessing) architecture.
--optimized for AVX2 instructions.
--Copyright (c) 2018-2024, Weijie ZHANG, GeoHohai, Hohai University.
************************************************************************************/
/************************************************************************************
DEM-Common.h: defines all the common auguments in the DEM calculations.
************************************************************************************/

#pragma once

#ifdef __ANDROID__
#define win32 0
#elif __linux__
#define win32 0
#elif _WIN32
#define win32 1
#endif

#define PI 3.1415926535f
#define nc 2.7182818285f