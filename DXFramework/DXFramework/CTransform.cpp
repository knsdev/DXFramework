#include "stdafx.h"
#include "CTransform.h"

CTransform::CTransform()
{
	DirectX::XMStoreFloat4x4(&m_worldMatrix, DirectX::XMMatrixIdentity());
}

CTransform::CTransform(const DirectX::XMMATRIX& worldMatrix)
{
	DirectX::XMStoreFloat4x4(&m_worldMatrix, worldMatrix);
}

CTransform::~CTransform()
{
}

DirectX::XMVECTOR CTransform::GetPosition()
{
	DirectX::XMMATRIX matrix = DirectX::XMLoadFloat4x4(&m_worldMatrix);

	DirectX::XMVECTOR pos;
	DirectX::XMVECTOR rotationQuat;
	DirectX::XMVECTOR scale;
	DirectX::XMMatrixDecompose(&scale, &rotationQuat, &pos, matrix);
	return pos;
}

DirectX::XMVECTOR CTransform::GetRotationQuat()
{
	DirectX::XMMATRIX matrix = DirectX::XMLoadFloat4x4(&m_worldMatrix);

	DirectX::XMVECTOR pos;
	DirectX::XMVECTOR rotationQuat;
	DirectX::XMVECTOR scale;
	DirectX::XMMatrixDecompose(&scale, &rotationQuat, &pos, matrix);
	return pos;
}

DirectX::XMVECTOR CTransform::GetScale()
{
	DirectX::XMMATRIX matrix = DirectX::XMLoadFloat4x4(&m_worldMatrix);

	DirectX::XMVECTOR pos;
	DirectX::XMVECTOR rotationQuat;
	DirectX::XMVECTOR scale;
	DirectX::XMMatrixDecompose(&scale, &rotationQuat, &pos, matrix);
	return scale;
}

void CTransform::Translate(DirectX::XMVECTOR translation, bool relativeToLocal)
{
	DirectX::XMMATRIX worldMatrix = DirectX::XMLoadFloat4x4(&m_worldMatrix);

	DirectX::XMVECTOR pos;
	DirectX::XMVECTOR rotationQuat;
	DirectX::XMVECTOR scale;
	DirectX::XMMatrixDecompose(&scale, &rotationQuat, &pos, worldMatrix);

	if (relativeToLocal)
	{
		DirectX::XMMATRIX rotationMatrix = DirectX::XMMatrixRotationQuaternion(rotationQuat);
		translation = DirectX::XMVector3Transform(translation, rotationMatrix);
	}

	DirectX::XMMATRIX translationMatrix = DirectX::XMMatrixTranslationFromVector(translation);
	pos = DirectX::XMVector3Transform(pos, translationMatrix);

	worldMatrix = DirectX::XMMatrixScalingFromVector(scale) * DirectX::XMMatrixRotationQuaternion(rotationQuat) * DirectX::XMMatrixTranslationFromVector(pos);

	DirectX::XMStoreFloat4x4(&m_worldMatrix, worldMatrix);
}

void CTransform::RotateAroundX(float angle)
{
	DirectX::XMMATRIX worldMatrix = DirectX::XMLoadFloat4x4(&m_worldMatrix);
	worldMatrix = DirectX::XMMatrixRotationX(angle) * worldMatrix;
	DirectX::XMStoreFloat4x4(&m_worldMatrix, worldMatrix);
}

void CTransform::RotateAroundY(float angle)
{
	DirectX::XMMATRIX worldMatrix = DirectX::XMLoadFloat4x4(&m_worldMatrix);
	worldMatrix = DirectX::XMMatrixRotationY(angle) * worldMatrix;
	DirectX::XMStoreFloat4x4(&m_worldMatrix, worldMatrix);
}

void CTransform::RotateAroundZ(float angle)
{
	DirectX::XMMATRIX worldMatrix = DirectX::XMLoadFloat4x4(&m_worldMatrix);
	worldMatrix = DirectX::XMMatrixRotationZ(angle) * worldMatrix;
	DirectX::XMStoreFloat4x4(&m_worldMatrix, worldMatrix);
}
