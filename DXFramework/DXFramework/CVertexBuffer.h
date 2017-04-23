#pragma once
#include "stdafx.h"
class CGraphics;
#include "CGraphics.h"
#include "CSysWindow.h"

class CVertexBuffer
{
public:
	CVertexBuffer(CGraphics* pGraphics, CSysWindow* pSysWindow);
	~CVertexBuffer();

	void Create(const void* pData, UINT num, UINT stride, D3D11_USAGE usage, UINT cpuAccessFlags);
	void Destroy();
	void Bind(UINT offset = 0);
	void Unbind();
	void Update(const void* pData, UINT num, UINT stride);

	UINT GetSize() { return m_num * m_stride; }

private:
	ID3D11Buffer* m_pBuffer;
	CGraphics* m_pGraphics;
	CSysWindow* m_pSysWindow;
	UINT m_num;
	UINT m_stride;
};