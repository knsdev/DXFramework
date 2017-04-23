#pragma once
#pragma once
#include "stdafx.h"
#include "IComponent.h"
#include "CTransform.h"

class CCameraMovement : public IComponent
{
public:
	CCameraMovement();
	virtual ~CCameraMovement();

	void Start() override;
	void Update(float deltaTime) override;

private:
	CTransform* m_pTransform;
	DirectX::XMFLOAT4X4 m_initWorldMatrix;
};