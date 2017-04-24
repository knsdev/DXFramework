#pragma once
#include "stdafx.h"
#include "SModel.h"
#include "CTexture2D.h"
#include "CShader.h"

namespace dxfw
{
	class CTexture2D;
	class CShader;

	struct SRenderCommand
	{
		DirectX::XMFLOAT4X4 worldMatrix;
		SModel* pModel;
		CTexture2D* pTexture;
		CShader* pVertexShader;
		CShader* pPixelShader;
		// TODO: bool isStatic; to separate static and dynamic gameObjects
	};
}
