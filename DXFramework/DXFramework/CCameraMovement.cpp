#include "stdafx.h"
#include "CCameraMovement.h"
#include "CTimer.h"
#include "CTestApp.h"

namespace dxfw
{
	CCameraMovement::CCameraMovement()
	{
	}

	CCameraMovement::~CCameraMovement()
	{
	}

	void CCameraMovement::Start()
	{
		m_pTransform = GetComponent<CTransform>();
		m_initWorldMatrix = *(m_pTransform->GetWorldMatrix());
	}

	void CCameraMovement::Update(float deltaTime)
	{
		float speed = 10.0f;
		float rotationSpeed = 2.0f;

		CTestApp* pTestApp = dynamic_cast<CTestApp*>(GetApp());
		if (pTestApp != nullptr)
		{
			auto inputManager = pTestApp->GetInputManager();
			if (inputManager->GetKeyState(EKeyCode::D))
			{
				m_pTransform->Translate(DirectX::XMVectorSet(speed * deltaTime, 0, 0, 0), false);
			}
			else if (inputManager->GetKeyState(EKeyCode::A))
			{
				m_pTransform->Translate(DirectX::XMVectorSet(-speed * deltaTime, 0, 0, 0), false);
			}
			if (inputManager->GetKeyState(EKeyCode::W))
			{
				m_pTransform->Translate(DirectX::XMVectorSet(0, 0, speed * deltaTime, 0), false);
			}
			else if (inputManager->GetKeyState(EKeyCode::S))
			{
				m_pTransform->Translate(DirectX::XMVectorSet(0, 0, -speed * deltaTime, 0), false);
			}

			if (inputManager->GetKeyState(EKeyCode::Space))
			{
				m_pTransform->Translate(DirectX::XMVectorSet(0, speed * deltaTime, 0, 0), false);
			}
			else if (inputManager->GetKeyState(EKeyCode::Shift))
			{
				m_pTransform->Translate(DirectX::XMVectorSet(0, -speed * deltaTime, 0, 0), false);
			}

			if (inputManager->GetKeyState(EKeyCode::Q))
			{
				m_pTransform->RotateAroundX(-rotationSpeed * deltaTime);
			}
			else if (inputManager->GetKeyState(EKeyCode::E))
			{
				m_pTransform->RotateAroundX(rotationSpeed * deltaTime);
			}
		}
	}
}
