#pragma once
#include "stdafx.h"
#include "IComponent.h"
#include "CTransform.h"

namespace dxfw
{
	class CTestScript : public IComponent
	{
	public:
		CTestScript();
		virtual ~CTestScript();

		void Start() override;
		void Update(float deltaTime) override;
		void FixedUpdate(float deltaTime) override;

	private:
		CTransform* m_pTransform;
		float m_angle;
		DirectX::XMFLOAT4X4 m_initWorldMatrix;
	};
}
