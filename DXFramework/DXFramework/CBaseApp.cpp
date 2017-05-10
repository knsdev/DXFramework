#include "stdafx.h"
#include "CBaseApp.h"

namespace dxfw
{
	CBaseApp::CBaseApp(const SAppConfig& config)
		: m_config(config)
	{
		m_pSysWindow = std::make_unique<CSysWindow>(static_cast<ISysWinEventHandler*>(this), m_config);
		m_pGraphics = std::make_unique<CGraphics>(m_config);
		m_pResourceManager = std::make_unique<CResourceManager>(m_pGraphics.get(), m_pSysWindow.get());
		m_pSceneManager = std::make_unique<CSceneManager>(m_pResourceManager.get(), m_pGraphics.get(), this);
		m_pInputManager = std::make_unique<CInputManager>();

		m_pGraphics->SetDependencies(m_pSysWindow.get(), m_pResourceManager.get());
	}

	CBaseApp::~CBaseApp()
	{
	}

	void CBaseApp::Run()
	{
		m_pSysWindow->Init();
		m_pGraphics->Init();

		m_prevTime = CTimer::GetSystemTimeInSeconds();
		m_fixedUpdateTimer = 0.0f;
		m_fixedRenderTimer = 0.0f;

		Start();

		m_pSysWindow->RunMessageLoop();
	}

	void CBaseApp::OnUpdate()
	{
		float maxTimeStep = m_pGraphics->GetScreenRefreshRate();
		float fixedDeltaTime = 1.0f / (float)m_config.numFixedUpdatesPerSecond;

		double currentTime = CTimer::GetSystemTimeInSeconds();
		float deltaTime = (float)(currentTime - m_prevTime);
		deltaTime = CMathHelper::Clamp(deltaTime, 0.0f, maxTimeStep);
		m_prevTime = currentTime;

		Update(deltaTime);

		m_fixedUpdateTimer += deltaTime;
		if (m_fixedUpdateTimer >= fixedDeltaTime)
		{
			m_fixedUpdateTimer -= fixedDeltaTime;
			FixedUpdate(fixedDeltaTime);
		}

		m_fixedRenderTimer += deltaTime;
		if (m_fixedRenderTimer >= maxTimeStep)
		{
			m_fixedRenderTimer -= maxTimeStep;
			Render();
			m_pGraphics->BeginDraw();
			m_pGraphics->EndDraw();
		}
	}

	void CBaseApp::OnResize(bool minimized, int clientWidth, int clientHeight)
	{
		// TODO: Resize BackBuffer
	}

	void CBaseApp::OnQuit()
	{
	}

	void CBaseApp::OnMsgKeyDown(WPARAM wParam, LPARAM lParam)
	{
		m_pInputManager->OnMsgKeyDown(wParam, lParam);
	}

	void CBaseApp::OnMsgKeyUp(WPARAM wParam, LPARAM lParam)
	{
		m_pInputManager->OnMsgKeyUp(wParam, lParam);
	}

	void CBaseApp::OnMsgMouseMove(WPARAM wParam, LPARAM lParam)
	{
		m_pInputManager->OnMsgMouseMove(wParam, lParam);
	}

	void CBaseApp::OnMsgMouseButtonDown(WPARAM wParam, LPARAM lParam, EKeyCode keyCode)
	{
		m_pInputManager->OnMsgMouseButtonDown(wParam, lParam, keyCode);
	}

	void CBaseApp::OnMsgMouseButtonUp(WPARAM wParam, LPARAM lParam, EKeyCode keyCode)
	{
		m_pInputManager->OnMsgMouseButtonUp(wParam, lParam, keyCode);
	}

	void CBaseApp::Start()
	{
	}

	void CBaseApp::Update(float deltaTime)
	{
		m_pSceneManager->Update(deltaTime);
	}

	void CBaseApp::FixedUpdate(float deltaTime)
	{
		m_pSceneManager->FixedUpdate(deltaTime);
	}

	void CBaseApp::Render()
	{
		m_pSceneManager->Render();
	}
}
