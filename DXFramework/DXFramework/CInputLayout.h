#pragma once
#include "stdafx.h"
class CGraphics;
#include "CGraphics.h"
#include "CSysWindow.h"
#include "EInputLayoutType.h"


class CInputLayout
{
public:
	CInputLayout(CGraphics* pGraphics, CSysWindow* pSysWindow);
	~CInputLayout();

	void Create(ID3DBlob* shaderBlob, D3D_PRIMITIVE_TOPOLOGY topology, EInputLayoutType layoutType);
	void Bind();
	void Unbind();

	D3D_PRIMITIVE_TOPOLOGY GetTopology() { return m_topology; }
	EInputLayoutType GetType() { return m_layoutType; }

private:
	ID3D11InputLayout* m_inputLayout;
	CGraphics* m_pGraphics;
	CSysWindow* m_pSysWindow;
	D3D_PRIMITIVE_TOPOLOGY m_topology;
	EInputLayoutType m_layoutType;
};