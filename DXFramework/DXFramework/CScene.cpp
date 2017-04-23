#include "stdafx.h"
#include "CScene.h"
#include "CMathHelper.h"
#include "CMeshRenderer.h"
#include "CTransform.h"

CScene::CScene(CResourceManager* pResourceManager, CGraphics* pGraphics, const char* pName, CBaseApp* pApp)
	:
	m_pResourceManager(pResourceManager),
	m_pGraphics(pGraphics),
	m_name(pName),
	m_pApp(pApp)
{
}

CScene::CScene(CResourceManager* pResourceManager, CGraphics* pGraphics, const std::vector<CGameObject>& gameObjects, const char* pName, CBaseApp* pApp)
	:
	m_pResourceManager(pResourceManager),
	m_pGraphics(pGraphics),
	m_gameObjects(gameObjects),
	m_name(pName),
	m_pApp(pApp)
{
}

CScene::~CScene()
{
}

void CScene::Init()
{
	for (IterGameObject it = m_gameObjects.begin(); it != m_gameObjects.end(); it++)
	{
		if (it->IsActive() && it->IsAlive())
		{
			it->Init();
		}
	}
}

void CScene::Start()
{
	for (IterGameObject it = m_gameObjects.begin(); it != m_gameObjects.end(); it++)
	{
		if (it->IsActive() && it->IsAlive())
		{
			it->Start();
		}
	}
}

void CScene::OnUnload()
{

}

void CScene::Update(float deltaTime)
{
	// Update GameObjects
	for (IterGameObject it = m_gameObjects.begin(); it != m_gameObjects.end(); it++)
	{
		if (it->IsActive() && it->IsAlive())
		{
			it->Update(deltaTime);
		}
	}
	// Delete dead GameObjects
	for (IterGameObject it = m_gameObjects.begin(); it != m_gameObjects.end(); it++)
	{
		if (!it->IsAlive())
		{
			DeleteGameObject(*it);
		}
	}
}

void CScene::FixedUpdate(float deltaTime)
{
	// Update GameObjects
	for (IterGameObject it = m_gameObjects.begin(); it != m_gameObjects.end(); it++)
	{
		if (it->IsActive() && it->IsAlive())
		{
			it->FixedUpdate(deltaTime);
		}
	}
}

void CScene::Render()
{
	// Find the Main Camera
	for (IterGameObject it = m_gameObjects.begin(); it != m_gameObjects.end(); it++)
	{
		CGameObject& obj = *it;

		CCamera* pCamera = obj.GetComponent<CCamera>();
		if (pCamera != nullptr)
		{
			// Get Camera's View- and Projection-Matrix
			DirectX::XMMATRIX mat_view = DirectX::XMLoadFloat4x4(pCamera->GetViewMatrix());
			DirectX::XMMATRIX mat_projection = DirectX::XMLoadFloat4x4(pCamera->GetProjectionMatrix());
			// Store it in Graphics
			m_pGraphics->SetViewMatrix(mat_view);
			m_pGraphics->SetProjectionMatrix(mat_projection);
			break;
		}
	}

	// Try to get RendererComponents of GameObjects, then pass RenderingCommands to Graphics
	for (IterGameObject it = m_gameObjects.begin(); it != m_gameObjects.end(); it++)
	{
		CGameObject& obj = *it;
		if (obj.IsActive() && obj.IsAlive())
		{
			CTransform* pTransform = obj.GetComponent<CTransform>();
			if (pTransform != nullptr)
			{
				DirectX::XMMATRIX worldMatrix = DirectX::XMLoadFloat4x4(pTransform->GetWorldMatrix());

				CMeshRenderer* pMeshRenderer = obj.GetComponent<CMeshRenderer>();
				if (pMeshRenderer != nullptr)
				{
					std::string& modelFileName = pMeshRenderer->GetModelFileName();
					std::string& textureFileName = pMeshRenderer->GetTextureFileName();
					std::string& vertexShaderFileName = pMeshRenderer->GetShaderFileName(EShaderType::VertexShader);
					std::string& pixelShaderFileName = pMeshRenderer->GetShaderFileName(EShaderType::PixelShader);

					SModel* pModel = m_pResourceManager->GetModel(modelFileName);
					CTexture2D* pTexture = m_pResourceManager->GetTexture(textureFileName);
					CShader* pVertexShader = m_pResourceManager->GetShader(EShaderType::VertexShader, vertexShaderFileName);
					CShader* pPixelShader = m_pResourceManager->GetShader(EShaderType::PixelShader, pixelShaderFileName);

					SRenderCommand command;
					DirectX::XMStoreFloat4x4(&command.worldMatrix, worldMatrix);
					command.pModel = pModel;
					command.pTexture = pTexture;
					command.pVertexShader = pVertexShader;
					command.pPixelShader = pPixelShader;

					m_pGraphics->AddRenderCommand(command);
				}
			}
		}
	}
}

CGameObject& CScene::CreateGameObject(const char* pName)
{
	m_gameObjects.push_back(CGameObject(pName, CMathHelper::GetNewGUID(), m_pApp));
	CGameObject& newObj = m_gameObjects.back();
	newObj.Init();
	newObj.Start();

	return newObj;
}

CGameObject& CScene::CreateGameObject(const char* pName, std::vector<IComponent*> components)
{
	m_gameObjects.push_back(CGameObject(pName, components, CMathHelper::GetNewGUID(), m_pApp));
	CGameObject& newObj = m_gameObjects.back();
	newObj.Init();
	newObj.Start();

	return newObj;
}

void CScene::DestroyGameObject(CGameObject& gameObject)
{
	if (gameObject.IsAlive())
	{
		gameObject.OnDestroy();
	}
}

CGameObject* CScene::FindGameObject(const char* pName)
{
	IterGameObject it = std::find_if(m_gameObjects.begin(), m_gameObjects.end(), [pName](const CGameObject& obj)
	{
		return (obj.IsAlive() && strcmp(obj.GetName(), pName) == 0);
	});

	if (it != m_gameObjects.end())
	{
		return &(*it);
	}

	return nullptr;
}

void CScene::DeleteGameObject(CGameObject& gameObject)
{
	IterGameObject it = std::find_if(m_gameObjects.begin(), m_gameObjects.end(), [gameObject](const CGameObject& obj)
	{
		return (&gameObject == &obj);
	});

	if (it != m_gameObjects.end())
	{
		std::swap(*it, m_gameObjects.back());
		m_gameObjects.pop_back();
	}
}
