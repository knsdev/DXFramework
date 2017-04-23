#pragma once
#include "stdafx.h"
#include "SModel.h"
class CTexture2D;
#include "CTexture2D.h"
class CShader;
#include "CShader.h"

struct SRenderCommand
{
	DirectX::XMFLOAT4X4 worldMatrix;
	SModel* pModel;
	CTexture2D* pTexture;
	CShader* pVertexShader;
	CShader* pPixelShader;
	// TODO: bool isStatic; to separate static and dynamic gameObjects
};