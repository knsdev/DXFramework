#include "stdafx.h"
#include "CTransform.h"

namespace dxfw
{
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
		return rotationQuat;
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

	void CTransform::RotateAroundXLocal(float angle)
	{
		DirectX::XMMATRIX worldMatrix = DirectX::XMLoadFloat4x4(&m_worldMatrix);
		worldMatrix = DirectX::XMMatrixRotationX(angle) * worldMatrix;
		DirectX::XMStoreFloat4x4(&m_worldMatrix, worldMatrix);
	}

	void CTransform::RotateAroundYLocal(float angle)
	{
		DirectX::XMMATRIX worldMatrix = DirectX::XMLoadFloat4x4(&m_worldMatrix);
		worldMatrix = DirectX::XMMatrixRotationY(angle) * worldMatrix;
		DirectX::XMStoreFloat4x4(&m_worldMatrix, worldMatrix);
	}

	void CTransform::RotateAroundZLocal(float angle)
	{
		DirectX::XMMATRIX worldMatrix = DirectX::XMLoadFloat4x4(&m_worldMatrix);
		worldMatrix = DirectX::XMMatrixRotationZ(angle) * worldMatrix;
		DirectX::XMStoreFloat4x4(&m_worldMatrix, worldMatrix);
	}

	void CTransform::RotateAroundAxis(const DirectX::XMFLOAT3& axis, float angle, bool relativeToLocal)
	{
		DirectX::XMMATRIX worldMatrix = DirectX::XMLoadFloat4x4(&m_worldMatrix);

		if (relativeToLocal)
		{
			DirectX::XMVECTOR axisVec = DirectX::XMVector3Normalize(XMLoadFloat3(&axis));
			DirectX::XMMATRIX rotMat = DirectX::XMMatrixRotationNormal(axisVec, angle);

			worldMatrix = rotMat * worldMatrix;
		}
		else
		{
			// get rotation from worldMatrix
			DirectX::XMVECTOR rotQuat = GetRotationQuat();

			// calculate delta rotation from axis and angle
			DirectX::XMVECTOR axisVec = DirectX::XMVector3Normalize(XMLoadFloat3(&axis));
			DirectX::XMVECTOR rotQuatDelta = DirectX::XMQuaternionRotationAxis(axisVec, angle);

			// multiply current rotation by delta rotation
			DirectX::XMVECTOR rotQuatResult = DirectX::XMQuaternionMultiply(rotQuat, rotQuatDelta);

			// convert to matrix
			DirectX::XMMATRIX rotMatResult = DirectX::XMMatrixRotationQuaternion(rotQuatResult);

			// keep position
			rotMatResult.r[3] = worldMatrix.r[3];

			// set rotation of worldMatrix
			worldMatrix = rotMatResult;
		}

		DirectX::XMStoreFloat4x4(&m_worldMatrix, worldMatrix);
	}
}
