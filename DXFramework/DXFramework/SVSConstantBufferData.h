#pragma once
#include "stdafx.h"

namespace dxfw
{
	struct SVSConstantBufferData
	{
		DirectX::XMMATRIX world;
		DirectX::XMMATRIX view;
		DirectX::XMMATRIX projection;
	};
}
