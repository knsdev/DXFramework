#pragma once
#include "stdafx.h"
#include "CBaseApp.h"
#include "SAppConfig.h"
#include "ISysWinEventHandler.h"
#include "CShader.h"
#include "CInputLayout.h"
#include "CVertexBuffer.h"
#include "CIndexBuffer.h"
#include "CConstantBuffer.h"
#include "CTexture2D.h"
#include "CTransform.h"
#include "CMeshRenderer.h"
#include "CCamera.h"
#include "CCameraMovement.h"
#include "CTestScript.h"

class CTestApp : public CBaseApp
{
public:
	CTestApp(const SAppConfig& config);
	virtual ~CTestApp();

public:
	// ISysWinEventHandler
	virtual void OnResize(bool minimized, int clientWidth, int clientHeight) override;
	virtual void OnQuit() override;

	// CBaseApp
	virtual void Start() override;
	virtual void Update(float deltaTime) override;
	virtual void FixedUpdate(float deltaTime) override;
	virtual void Render() override;

private:
	std::unique_ptr<CShader> m_pVertexShader;
	std::unique_ptr<CShader> m_pPixelShader;
	std::unique_ptr<CInputLayout> m_pInputLayout;
	std::unique_ptr<CVertexBuffer> m_pVertexBuffer;
	std::unique_ptr<CIndexBuffer> m_pIndexBuffer;
	std::unique_ptr<CConstantBuffer> m_pConstantBuffer;
	std::unique_ptr<CTexture2D> m_pTexture2D;

	DirectX::XMMATRIX mat_world;
	DirectX::XMMATRIX mat_view;
	DirectX::XMMATRIX mat_proj;
	DirectX::XMVECTOR vec_camPos;
	DirectX::XMVECTOR vec_camTarget;
	DirectX::XMVECTOR vec_up;
	float m_angle;

	SModel* m_pModel;
};