#pragma once
#include "stdafx.h"
class CGraphics;
#include "CGraphics.h"
#include "EShaderType.h"

class CTexture2D
{
public:
	CTexture2D() {};
	CTexture2D(CGraphics* pGraphics);
	~CTexture2D();

	void Create(UINT width, UINT height, UINT color, D3D11_USAGE usage);
	void Create(const char* pFileName, D3D11_USAGE usage);

	void Bind(EShaderType shaderType);
	void Unbind(EShaderType shaderType);

	const ID3D11Texture2D* Get() { return m_pTexture; }
	const D3D11_TEXTURE2D_DESC GetDesc() { D3D11_TEXTURE2D_DESC pDesc;  m_pTexture->GetDesc(&pDesc); return pDesc; }

private:
	CGraphics* m_pGraphics;
	CComPtr<ID3D11Texture2D> m_pTexture;
	CComPtr<ID3D11ShaderResourceView> m_pShaderResView;
};