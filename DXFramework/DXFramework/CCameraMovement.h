#pragma once
#pragma once
#include "stdafx.h"
#include "IComponent.h"
#include "CTransform.h"

namespace dxfw
{
	class CCameraMovement : public IComponent
	{
	public:
		CCameraMovement();
		virtual ~CCameraMovement();

		void Start() override;
		void FixedUpdate(float deltaTime) override;

	private:
		void SetMouseCursorToCenter();

	private:
		CTransform* m_pTransform;
		POINT m_mousePos = { 0, 0 };
	};
}
