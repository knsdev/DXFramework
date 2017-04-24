#pragma once
#include "stdafx.h"

namespace dxfw
{
	struct SVertexPos
	{
		float pos[3];
	};

	struct SVertexPosUV
	{
		float pos[3];
		float uv[2];
	};

	struct SVertexPosUVNormal
	{
		float pos[3];
		float uv[2];
		float normal[3];
	};
}
