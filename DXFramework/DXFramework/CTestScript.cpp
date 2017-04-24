#include "stdafx.h"
#include "CTestScript.h"
#include "CTimer.h"
#include "CTestApp.h"

namespace dxfw
{
	CTestScript::CTestScript()
		:
		m_angle(0)
	{
	}

	CTestScript::~CTestScript()
	{
	}

	void CTestScript::Start()
	{
		m_pTransform = GetComponent<CTransform>();
		m_initWorldMatrix = *(m_pTransform->GetWorldMatrix());
	}

	void CTestScript::Update(float deltaTime)
	{
	}

	void CTestScript::FixedUpdate(float deltaTime)
	{
		m_pTransform->SetWorldMatrix(DirectX::XMMatrixRotationY(m_angle) * DirectX::XMLoadFloat4x4(&m_initWorldMatrix));
		m_angle += deltaTime;
	}
}

