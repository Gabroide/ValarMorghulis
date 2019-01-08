#ifndef __DebugDraw_h__
#define _DebugDraw_h__

#include "MathGeoLib.h"

typedef math::float3 ddVec3;

typedef const ddVec3& ddVec3_In;
typedef       ddVec3& ddVec3_Out;

#define DEBUG_DRAW_VEC3_TYPE_DEFINED 1

typedef math::float4x4 ddMat4x4;

typedef const ddMat4x4& ddMat4x4_In;
typedef       ddMat4x4& ddMat4x4_Out;

#define DEBUG_DRAW_MAT4X4_TYPE_DEFINED 1

#include "debug_draw.hpp"

#endif // __DebugDraw_h__
