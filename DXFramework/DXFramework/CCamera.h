#pragma once
#include "stdafx.h"
#include "IComponent.h"
#include "CTransform.h"

class CCamera : public IComponent
{
public:
	CCamera();
	virtual ~CCamera();

	void Start() override;
	void Update(float deltaTime) override;

	void SetProjectionMatrix(float fovAngleY, float aspectRatio, float nearZ = 1.0f, float farZ = 1000.0f);

	DirectX::XMFLOAT4X4* GetViewMatrix() { return &m_viewMatrix; }
	DirectX::XMFLOAT4X4* GetProjectionMatrix() { return &m_projectionMatrix; }

private:
	void UpdateViewMatrix();

private:
	DirectX::XMFLOAT4X4 m_viewMatrix;
	DirectX::XMFLOAT4X4 m_projectionMatrix;
	CTransform* m_pTransform;
};