#include "stdafx.h"
#include "CIndexBuffer.h"

CIndexBuffer::CIndexBuffer(CGraphics* pGraphics, CSysWindow* pSysWindow)
	:
	m_pBuffer(nullptr),
	m_pGraphics(pGraphics),
	m_pSysWindow(pSysWindow),
	m_numIndices(0)
{
}

CIndexBuffer::~CIndexBuffer()
{
	Destroy();
}

void CIndexBuffer::Create(const DWORD* pIndices, UINT numIndices, D3D11_USAGE usage, UINT cpuAccessFlags)
{
	m_numIndices = numIndices;

	D3D11_BUFFER_DESC indexBufferDesc;
	ZeroMemory(&indexBufferDesc, sizeof(D3D11_BUFFER_DESC));
	indexBufferDesc.Usage = usage;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.ByteWidth = sizeof(DWORD) * numIndices;
	indexBufferDesc.CPUAccessFlags = cpuAccessFlags;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA subResData;
	subResData.pSysMem = pIndices;
	subResData.SysMemPitch = 0;
	subResData.SysMemSlicePitch = 0;

	m_pGraphics->GetDevice()->CreateBuffer(&indexBufferDesc, &subResData, &m_pBuffer);
}

void CIndexBuffer::Destroy()
{
	if (m_pBuffer != nullptr)
	{
		m_pBuffer->Release();
		m_pBuffer = nullptr;
	}
}

void CIndexBuffer::Bind()
{
	m_pGraphics->GetImmediateContext()->IASetIndexBuffer(m_pBuffer, DXGI_FORMAT_R32_UINT, 0);
}

void CIndexBuffer::Unbind()
{
	m_pGraphics->GetImmediateContext()->IASetIndexBuffer(NULL, DXGI_FORMAT_R32_UINT, 0);
}

void CIndexBuffer::Update(DWORD* pIndices, UINT numIndices)
{
	D3D11_MAPPED_SUBRESOURCE mapped;
	m_pGraphics->GetImmediateContext()->Map(m_pBuffer, 0, D3D11_MAP_WRITE_DISCARD, NULL, &mapped);
	memcpy(mapped.pData, pIndices, sizeof(DWORD) * numIndices);
	mapped.RowPitch = 0;
	mapped.DepthPitch = 0;
	m_pGraphics->GetImmediateContext()->Unmap(m_pBuffer, 0);
}

