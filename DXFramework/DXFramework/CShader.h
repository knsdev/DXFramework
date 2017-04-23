#pragma once
#include "stdafx.h"
#include "CGraphics.h"
#include "CSysWindow.h"
#include "EShaderType.h"
#include "EInputLayoutType.h"
class CInputLayout;
#include "CInputLayout.h"

class CShader
{
public:
	CShader(const wchar_t* filePath, const char* entryPoint, EShaderType type, CGraphics* pGraphics, CSysWindow* pSysWindow);
	~CShader();

	void Compile();
	void Bind();
	void Unbind();
	CInputLayout* CreateInputLayout(EInputLayoutType inputLayoutType, D3D_PRIMITIVE_TOPOLOGY topology);

	ID3DBlob* GetShaderBlob();
	ID3D11VertexShader* GetVertexShader();
	ID3D11PixelShader* GetPixelShader();

	CInputLayout* GetInputLayout() { return m_pInputLayout; }

private:
	CShader();
	CShader(const CShader& other);

private:
	const wchar_t* m_filePath;
	const char* m_entryPoint;
	EShaderType m_type;

	ID3DBlob* m_shaderBlob;
	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;

	CInputLayout* m_pInputLayout;

	CGraphics* m_pGraphics;
	CSysWindow* m_pSysWindow;
};

void OutputShaderErrorMessage(ID3D10Blob* errorMessage, HWND hwnd, wchar_t* pShaderFilename);