#include "stdafx.h"
#include "CTestApp.h"
#include "CMazeDepthFirst.h"

CTestApp::CTestApp(const SAppConfig& config)
	: CBaseApp(config)
{
}

CTestApp::~CTestApp()
{
}

void CTestApp::OnResize(bool minimized, int clientWidth, int clientHeight)
{
	CBaseApp::OnResize(minimized, clientWidth, clientHeight);
}

void CTestApp::OnQuit()
{
	CBaseApp::OnQuit();
}

void CTestApp::Start()
{
	CBaseApp::Start();

	CScene sceneTest(GetResourceManager(), GetGraphics(), "Scene_Test", this);

	{
		CGameObject& obj = sceneTest.CreateGameObject("Camera");
		CTransform* pTrans = obj.AddComponent<CTransform>();
		pTrans->SetWorldMatrix(DirectX::XMMatrixIdentity() * DirectX::XMMatrixTranslation(5, 5, 0));
		CCamera* camera = obj.AddComponent<CCamera>();
		camera->SetProjectionMatrix(DirectX::XM_PI / 2.0f, (float)m_pSysWindow->GetClientWidth() / (float)m_pSysWindow->GetClientHeight());
		obj.AddComponent<CCameraMovement>();
	}

	CMazeDepthFirst maze;
	SMazeParams params;
	params.seed = (unsigned int) CTimer::GetSystemTimeInSeconds();
	params.width = 5;
	params.height = 5;
	maze.Generate(params);
	maze.ShowDebugMaze();

	float offset = 2.0f;
	float cubeOffset = 0.0f;
	float cubeScale = 1.0f;
	float golemScale = 0.25f;
	float golemOffsetY = -1.05f;
	float groundOffsetY = -2.0f;

	bool* pBoolArray = maze.GetBoolArray();
	for (int y = 0; y < params.height * 3; y++)
	{
		for (int x = 0; x < params.width * 3; x++)
		{
			if (pBoolArray[x + params.width * 3 * y])
			{
				CGameObject& obj = sceneTest.CreateGameObject("Cube");
				CTransform* pTrans = obj.AddComponent<CTransform>();
				pTrans->SetWorldMatrix(DirectX::XMMatrixIdentity() * DirectX::XMMatrixScaling(cubeScale, cubeScale, cubeScale) * DirectX::XMMatrixTranslation(x * offset, cubeOffset, y * offset));
				CMeshRenderer* pMeshRenderer = obj.AddComponent<CMeshRenderer>();
				pMeshRenderer->SetModelFileName("res/model_cube.obj");
				pMeshRenderer->SetTextureFileName("res/tex_cube_diffuse.tga");
				pMeshRenderer->SetShaderFileName(EShaderType::VertexShader, "shader/basic_vs.fx");
				pMeshRenderer->SetShaderFileName(EShaderType::PixelShader, "shader/basic_ps.fx");
			}
			else
			{
				{
					CGameObject& obj = sceneTest.CreateGameObject("Golem");
					CTransform* pTrans = obj.AddComponent<CTransform>();
					pTrans->SetWorldMatrix(DirectX::XMMatrixIdentity() * DirectX::XMMatrixScaling(golemScale, golemScale, golemScale) * DirectX::XMMatrixTranslation(x * offset, golemOffsetY, y * offset));
					CMeshRenderer* pMeshRenderer = obj.AddComponent<CMeshRenderer>();
					pMeshRenderer->SetModelFileName("res/model_golem.obj");
					pMeshRenderer->SetTextureFileName("res/tex_golem_diffuse.png");
					pMeshRenderer->SetShaderFileName(EShaderType::VertexShader, "shader/basic_vs.fx");
					pMeshRenderer->SetShaderFileName(EShaderType::PixelShader, "shader/basic_ps.fx");
					obj.AddComponent<CTestScript>();
				}
				{
					CGameObject& obj = sceneTest.CreateGameObject("Ground");
					CTransform* pTrans = obj.AddComponent<CTransform>();
					pTrans->SetWorldMatrix(DirectX::XMMatrixIdentity() * DirectX::XMMatrixScaling(cubeScale, cubeScale, cubeScale) * DirectX::XMMatrixTranslation(x * offset, groundOffsetY, y * offset));
					CMeshRenderer* pMeshRenderer = obj.AddComponent<CMeshRenderer>();
					pMeshRenderer->SetModelFileName("res/model_cube.obj");
					pMeshRenderer->SetTextureFileName("res/tex_metal_overlaping_plates_bolted_basecolor.png");
					pMeshRenderer->SetShaderFileName(EShaderType::VertexShader, "shader/basic_vs.fx");
					pMeshRenderer->SetShaderFileName(EShaderType::PixelShader, "shader/basic_ps.fx");
				}
			}
		}
	}


	m_pSceneManager->LoadScene(sceneTest, ESceneLoadOption::Additive);
}

void CTestApp::Update(float deltaTime)
{
	CBaseApp::Update(deltaTime);
}

void CTestApp::FixedUpdate(float deltaTime)
{
	CBaseApp::FixedUpdate(deltaTime);
}

void CTestApp::Render()
{
	CBaseApp::Render();
}
