#include "stdafx.h"
#include "CVertexBuffer.h"

CVertexBuffer::CVertexBuffer(CGraphics* pGraphics, CSysWindow* pSysWindow)
	:
	m_pBuffer(nullptr),
	m_pGraphics(pGraphics),
	m_pSysWindow(pSysWindow),
	m_num(0),
	m_stride(0)
{
}

CVertexBuffer::~CVertexBuffer()
{
	Destroy();
}

void CVertexBuffer::Create(const void* pData, UINT num, UINT stride, D3D11_USAGE usage, UINT cpuAccessFlags)
{
	m_num = num;
	m_stride = stride;

	D3D11_BUFFER_DESC vertBufferDesc = {};
	vertBufferDesc.Usage = usage;
	vertBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertBufferDesc.CPUAccessFlags = cpuAccessFlags;
	vertBufferDesc.ByteWidth = stride * num;
	vertBufferDesc.MiscFlags = 0;
	vertBufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA subResData = {};
	subResData.pSysMem = pData;
	subResData.SysMemPitch = 0;
	subResData.SysMemSlicePitch = 0;

	m_pGraphics->GetDevice()->CreateBuffer(&vertBufferDesc, &subResData, &m_pBuffer);
}

void CVertexBuffer::Destroy()
{
	if (m_pBuffer != nullptr)
	{
		m_pBuffer->Release();
		m_pBuffer = nullptr;
	}
}

void CVertexBuffer::Bind(UINT offset)
{
	ID3D11Buffer* buffers[1];
	buffers[0] = m_pBuffer;
	m_pGraphics->GetImmediateContext()->IASetVertexBuffers(0, 1, buffers, &m_stride, &offset);
}

void CVertexBuffer::Unbind()
{
	m_pGraphics->GetImmediateContext()->IASetVertexBuffers(0, 1, NULL, 0, 0);
}

void CVertexBuffer::Update(const void* pData, UINT num, UINT stride)
{
	D3D11_MAPPED_SUBRESOURCE mapped;
	m_pGraphics->GetImmediateContext()->Map(m_pBuffer, 0, D3D11_MAP_WRITE_DISCARD, NULL, &mapped);
	// Copy Data into the VertexBuffer
	memcpy(mapped.pData, pData, stride * num);
	mapped.RowPitch = 0;
	mapped.DepthPitch = 0;
	m_pGraphics->GetImmediateContext()->Unmap(m_pBuffer, 0);
}
