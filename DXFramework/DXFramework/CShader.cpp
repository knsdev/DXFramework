#include "stdafx.h"
#include "CShader.h"

namespace dxfw
{
	CShader::CShader(const wchar_t* filePath, const char* entryPoint, EShaderType type, CGraphics* pGraphics, CSysWindow* pSysWindow)
		:
		m_filePath(filePath),
		m_entryPoint(entryPoint),
		m_type(type),
		m_pGraphics(pGraphics),
		m_pSysWindow(pSysWindow),
		m_shaderBlob(NULL),
		m_vertexShader(NULL),
		m_pixelShader(NULL),
		m_pInputLayout(NULL)
	{
	}

	CShader::~CShader()
	{
		if (m_vertexShader)
			m_vertexShader->Release();
		if (m_pixelShader)
			m_pixelShader->Release();

		if (m_shaderBlob)
			m_shaderBlob->Release();

		delete m_pInputLayout;
	}

	void CShader::Compile()
	{
		ID3DBlob* errorBlob = NULL;

		switch (m_type)
		{
		case EShaderType::VertexShader:
		{
			HRESULT hr = D3DCompileFromFile(m_filePath, NULL, NULL, m_entryPoint, "vs_5_0", NULL, NULL, &m_shaderBlob, &errorBlob);
			if (hr != S_OK)
			{
				OutputShaderErrorMessage(errorBlob, m_pSysWindow->GetHandle(), m_filePath);
				break;
			}
			m_pGraphics->GetDevice()->CreateVertexShader(m_shaderBlob->GetBufferPointer(), m_shaderBlob->GetBufferSize(), NULL, &m_vertexShader);
			break;
		}
		case EShaderType::PixelShader:
		{
			HRESULT hr = D3DCompileFromFile(m_filePath, NULL, NULL, m_entryPoint, "ps_5_0", NULL, NULL, &m_shaderBlob, &errorBlob);
			if (hr != S_OK)
			{
				OutputShaderErrorMessage(errorBlob, m_pSysWindow->GetHandle(), m_filePath);
				break;
			}
			m_pGraphics->GetDevice()->CreatePixelShader(m_shaderBlob->GetBufferPointer(), m_shaderBlob->GetBufferSize(), NULL, &m_pixelShader);
			break;
		}
		}
	}

	void CShader::Bind()
	{
		if (m_vertexShader)
		{
			m_pGraphics->GetImmediateContext()->VSSetShader(m_vertexShader, NULL, 0);
		}
		else if (m_pixelShader)
		{
			m_pGraphics->GetImmediateContext()->PSSetShader(m_pixelShader, NULL, 0);
		}
	}

	void CShader::Unbind()
	{
		if (m_vertexShader)
		{
			m_pGraphics->GetImmediateContext()->PSSetShader(NULL, NULL, 0);
		}
		else if (m_pixelShader)
		{
			m_pGraphics->GetImmediateContext()->VSSetShader(NULL, NULL, 0);
		}
	}

	CInputLayout* CShader::CreateInputLayout(EInputLayoutType inputLayoutType, D3D_PRIMITIVE_TOPOLOGY topology)
	{
		if (m_type != EShaderType::VertexShader)
		{
			return nullptr;
		}
		if (m_pInputLayout != nullptr)
		{
			delete m_pInputLayout;
		}

		m_pInputLayout = new CInputLayout(m_pGraphics, m_pSysWindow);
		m_pInputLayout->Create(m_shaderBlob, topology, inputLayoutType);
		return m_pInputLayout;
	}

	ID3D11VertexShader* CShader::GetVertexShader()
	{
		return m_vertexShader;
	}

	ID3D11PixelShader* CShader::GetPixelShader()
	{
		return m_pixelShader;
	}

	ID3DBlob* CShader::GetShaderBlob()
	{
		return m_shaderBlob;
	}

	void OutputShaderErrorMessage(ID3D10Blob* errorMessage, HWND hwnd, const wchar_t* pShaderFilename)
	{
		unsigned long bufferSize;

		bufferSize = (unsigned long)errorMessage->GetBufferSize();

		size_t numCharsConverted;

		char* pError = (char*)(errorMessage->GetBufferPointer());
		wchar_t* pStr = new wchar_t[bufferSize];
		mbstowcs_s(&numCharsConverted, pStr, bufferSize, pError, bufferSize);

		MessageBox(hwnd, pStr, pShaderFilename, MB_OK);

		// Free Memory
		delete[] pStr;

		// Release the error message
		errorMessage->Release();
		errorMessage = 0;
	}
}
