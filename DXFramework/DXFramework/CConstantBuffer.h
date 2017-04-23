#pragma once
#include "stdafx.h"
#include "CGraphics.h"
#include "CSysWindow.h"

enum class EConstantBufferShaderType
{
	VertexShader,
	PixelShader,
};

class CConstantBuffer
{
public:
	CConstantBuffer(EConstantBufferShaderType shaderType, D3D11_USAGE usage, CGraphics* pGraphics, CSysWindow* pSysWindow);
	~CConstantBuffer();

	void Create(const void* pData, UINT size);
	void Bind();
	void Unbind();
	void Update(const void* pData, UINT size);

private:
	CComPtr<ID3D11Buffer> m_pBuffer;
	EConstantBufferShaderType m_shaderType;
	D3D11_USAGE m_usage;
	CGraphics* m_pGraphics;
	CSysWindow* m_pSysWindow;
};