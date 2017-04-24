#pragma once
#include "stdafx.h"
#include "CGraphics.h"
#include "CSysWindow.h"

namespace dxfw
{
	class CGraphics;

	class CIndexBuffer
	{
	public:
		CIndexBuffer(CGraphics* pGraphics, CSysWindow* pSysWindow);
		~CIndexBuffer();

		void Create(const DWORD* pIndices, UINT numIndices, D3D11_USAGE usage, UINT cpuAccessFlags);
		void Destroy();
		void Bind();
		void Unbind();
		void Update(DWORD* pIndices, UINT numIndices);

		UINT GetNumIndices() { return m_numIndices; }

	private:
		ID3D11Buffer* m_pBuffer;
		CGraphics* m_pGraphics;
		CSysWindow* m_pSysWindow;
		UINT m_numIndices;
	};
}