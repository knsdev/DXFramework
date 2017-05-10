#include "stdafx.h"
#include "CCamera.h"

namespace dxfw
{
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

	void CCamera::SetProjectionMatrixPerspective(float fovAngleY, float aspectRatio, float nearZ, float farZ)
	{
		DirectX::XMMATRIX perspectiveMatrix = DirectX::XMMatrixPerspectiveFovLH(fovAngleY, aspectRatio, nearZ, farZ);
		DirectX::XMStoreFloat4x4(&m_projectionMatrix, perspectiveMatrix);
	}

	void CCamera::SetProjectionMatrixOrtho(float width, float height, float nearZ, float farZ)
	{
		DirectX::XMMATRIX orthoMatrix = DirectX::XMMatrixOrthographicLH(width, height, nearZ, farZ);
		DirectX::XMStoreFloat4x4(&m_projectionMatrix, orthoMatrix);
	}

	void CCamera::UpdateViewMatrix()
	{
		DirectX::XMMATRIX transWorldMatrix = DirectX::XMLoadFloat4x4(m_pTransform->GetWorldMatrix());
		DirectX::XMVECTOR determinant = DirectX::XMMatrixDeterminant(transWorldMatrix);
		DirectX::XMMATRIX transInverseWorldMatrix = DirectX::XMMatrixInverse(&determinant, transWorldMatrix);

		DirectX::XMStoreFloat4x4(&m_viewMatrix, transInverseWorldMatrix);
	}
}