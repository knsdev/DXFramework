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
		SetMouseCursorToCenter();
		ShowCursor(FALSE);
	}

	void CCameraMovement::FixedUpdate(float deltaTime)
	{
		float speed = 10.0f;
		float rotationSpeed = 2.0f;
		bool local = true;

		CTestApp* pTestApp = dynamic_cast<CTestApp*>(GetApp());
		if (pTestApp != nullptr)
		{
			auto inputManager = pTestApp->GetInputManager();
			if (inputManager->GetKeyState(EKeyCode::D))
			{
				m_pTransform->Translate(DirectX::XMVectorSet(speed * deltaTime, 0, 0, 0), local);
			}
			else if (inputManager->GetKeyState(EKeyCode::A))
			{
				m_pTransform->Translate(DirectX::XMVectorSet(-speed * deltaTime, 0, 0, 0), local);
			}
			if (inputManager->GetKeyState(EKeyCode::W))
			{
				m_pTransform->Translate(DirectX::XMVectorSet(0, 0, speed * deltaTime, 0), local);
			}
			else if (inputManager->GetKeyState(EKeyCode::S))
			{
				m_pTransform->Translate(DirectX::XMVectorSet(0, 0, -speed * deltaTime, 0), local);
			}

			if (inputManager->GetKeyState(EKeyCode::Space))
			{
				m_pTransform->Translate(DirectX::XMVectorSet(0, speed * deltaTime, 0, 0), false);
			}
			else if (inputManager->GetKeyState(EKeyCode::Shift))
			{
				m_pTransform->Translate(DirectX::XMVectorSet(0, -speed * deltaTime, 0, 0), false);
			}

			POINT mousePos = inputManager->GetMousePosition();
			float deltaX = (float)(mousePos.x - m_mousePos.x);
			float deltaY = (float)(mousePos.y - m_mousePos.y);
			
			m_pTransform->RotateAroundAxis(DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f), deltaX * deltaTime, false);
			m_pTransform->RotateAroundXLocal(deltaY * deltaTime);

			m_mousePos = mousePos;
		}
	}

	void CCameraMovement::SetMouseCursorToCenter()
	{
		RECT rect;
		GetWindowRect(m_pApp->GetSysWindow()->GetHandle(), &rect);

		int width = m_pApp->GetSysWindow()->GetClientWidth();
		int height = m_pApp->GetSysWindow()->GetClientHeight();

		int mx = rect.left + width / 2;
		int my = rect.top + height / 2;
		SetCursorPos(mx, my);

		m_mousePos.x = mx;
		m_mousePos.y = my;
	}
}
