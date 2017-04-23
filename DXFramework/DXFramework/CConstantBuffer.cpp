#include "stdafx.h"
#include "CConstantBuffer.h"

CConstantBuffer::CConstantBuffer(EConstantBufferShaderType shaderType, D3D11_USAGE usage, CGraphics* pGraphics, CSysWindow* pSysWindow)
	:
	m_shaderType(shaderType),
	m_usage(usage),
	m_pGraphics(pGraphics),
	m_pSysWindow(pSysWindow)
{
}

CConstantBuffer::~CConstantBuffer()
{
}

void CConstantBuffer::Create(const void* pData, UINT size)
{
	HRESULT result = S_OK;

	D3D11_BUFFER_DESC cbufferDesc = {};
	cbufferDesc.Usage = m_usage;
	cbufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	if (size % 16 != 0)
	{
		throw std::exception("ConstantBuffer: ByteWidth value must be a multiple of 16");
	}
	cbufferDesc.ByteWidth = size;

	cbufferDesc.CPUAccessFlags = 0;
	cbufferDesc.StructureByteStride = 0;
	cbufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = pData;

	result = m_pGraphics->GetDevice()->CreateBuffer(&cbufferDesc, &initData, &m_pBuffer);
	if (FAILED(result))
	{
		throw std::exception("ConstantBuffer Create");
	}
}

void CConstantBuffer::Bind()
{
	ID3D11Buffer* buffers[1];
	buffers[0] = m_pBuffer;

	switch (m_shaderType)
	{
	case EConstantBufferShaderType::VertexShader:
		m_pGraphics->GetImmediateContext()->VSSetConstantBuffers(0, 1, buffers);
		break;
	case EConstantBufferShaderType::PixelShader:
		m_pGraphics->GetImmediateContext()->PSSetConstantBuffers(0, 1, buffers);
		break;
	default:
		break;
	}
}

void CConstantBuffer::Unbind()
{
	switch (m_shaderType)
	{
	case EConstantBufferShaderType::VertexShader:
		m_pGraphics->GetImmediateContext()->VSSetConstantBuffers(0, 0, NULL);
		break;
	case EConstantBufferShaderType::PixelShader:
		m_pGraphics->GetImmediateContext()->PSSetConstantBuffers(0, 0, NULL);
		break;
	default:
		break;
	}
}

void CConstantBuffer::Update(const void* pData, UINT size)
{
	UINT srcRowPitch = 0;
	UINT srcDepthPitch = 0;
	m_pGraphics->GetImmediateContext()->UpdateSubresource(m_pBuffer, 0, NULL, pData, srcRowPitch, srcDepthPitch);

	// TODO: alternate update method for per-frame-updates
	//m_pGraphics->GetImmediateContext()->Map()
}
