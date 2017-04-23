#include "stdafx.h"
#include "CCamera.h"

CCamera::CCamera()
{

}

CCamera::~CCamera()
{

}

void CCamera::Start()
{
	m_pTransform = GetComponent<CTransform>();
	assert(m_pTransform);

	UpdateViewMatrix();
}

void CCamera::Update(float deltaTime)
{
	UpdateViewMatrix();
}

void CCamera::SetProjectionMatrix(float fovAngleY, float aspectRatio, float nearZ, float farZ)
{
	DirectX::XMMATRIX mat_proj = DirectX::XMMatrixPerspectiveFovLH(fovAngleY, aspectRatio, nearZ, farZ);
	DirectX::XMStoreFloat4x4(&m_projectionMatrix, mat_proj);
}

void CCamera::UpdateViewMatrix()
{
	DirectX::XMMATRIX transWorldMatrix = DirectX::XMLoadFloat4x4(m_pTransform->GetWorldMatrix());
	DirectX::XMVECTOR determinant = DirectX::XMMatrixDeterminant(transWorldMatrix);
	DirectX::XMMATRIX transInverseWorldMatrix = DirectX::XMMatrixInverse(&determinant, transWorldMatrix);

	DirectX::XMStoreFloat4x4(&m_viewMatrix, transInverseWorldMatrix);
}
