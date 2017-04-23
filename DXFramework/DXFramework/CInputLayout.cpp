#include "stdafx.h"
#include "CInputLayout.h"

CInputLayout::CInputLayout(CGraphics* pGraphics, CSysWindow* pSysWindow)
	:
	m_pGraphics(pGraphics),
	m_pSysWindow(pSysWindow)
{
}

CInputLayout::~CInputLayout()
{
	if (m_inputLayout)
		m_inputLayout->Release();
}

void CInputLayout::Create(ID3DBlob* shaderBlob, D3D_PRIMITIVE_TOPOLOGY topology, EInputLayoutType layoutType)
{
	m_topology = topology;
	m_layoutType = layoutType;

	D3D11_INPUT_ELEMENT_DESC* pLayoutDesc = nullptr;
	UINT numElements = 0;

	switch (layoutType)
	{
	case EInputLayoutType::Pos:
		numElements = 1;
		pLayoutDesc = new D3D11_INPUT_ELEMENT_DESC[numElements];
		pLayoutDesc[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		break;
	case EInputLayoutType::PosUV:
		numElements = 2;
		pLayoutDesc = new D3D11_INPUT_ELEMENT_DESC[numElements];
		pLayoutDesc[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		pLayoutDesc[1] = { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		break;
	default:
		throw std::exception("Unknown InputLayoutType");
		break;
	}

	m_pGraphics->GetDevice()->CreateInputLayout(pLayoutDesc, numElements, shaderBlob->GetBufferPointer(), shaderBlob->GetBufferSize(), &m_inputLayout);

	delete[] pLayoutDesc;
}

void CInputLayout::Bind()
{
	m_pGraphics->GetImmediateContext()->IASetPrimitiveTopology(m_topology);
	m_pGraphics->GetImmediateContext()->IASetInputLayout(m_inputLayout);
}

void CInputLayout::Unbind()
{
	m_pGraphics->GetImmediateContext()->IASetInputLayout(NULL);
}