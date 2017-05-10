#pragma once
#include "stdafx.h"
#include "CSysWindow.h"
#include "ISysWinEventHandler.h"
#include "SAppConfig.h"
#include "CGraphics.h"
#include "CTimer.h"
#include "CMathHelper.h"
#include "CResourceManager.h"
#include "CSceneManager.h"
#include "CInputManager.h"

namespace dxfw
{
	class CSceneManager;

	class CBaseApp : public ISysWinEventHandler
	{
	public:
		CBaseApp(const SAppConfig& config);
		virtual ~CBaseApp();

		void Run();

	public:
		// ISysWinEventHandler
		void OnUpdate() final;
		virtual void OnResize(bool minimized, int clientWidth, int clientHeight) override;
		virtual void OnQuit() override;
		virtual void OnMsgKeyDown(WPARAM wParam, LPARAM lParam) override;
		virtual void OnMsgKeyUp(WPARAM wParam, LPARAM lParam) override;
		virtual void OnMsgMouseMove(WPARAM wParam, LPARAM lParam) override;
		virtual void OnMsgMouseButtonDown(WPARAM wParam, LPARAM lParam, EKeyCode keyCode) override;
		virtual void OnMsgMouseButtonUp(WPARAM wParam, LPARAM lParam, EKeyCode keyCode) override;

		CGraphics* GetGraphics() { return m_pGraphics.get(); }
		CSysWindow* GetSysWindow() { return m_pSysWindow.get(); }
		CResourceManager* GetResourceManager() { return m_pResourceManager.get(); }
		CSceneManager* GetSceneManager() { return m_pSceneManager.get(); }
		CInputManager* GetInputManager() { return m_pInputManager.get(); }

	protected:
		virtual void Start();
		virtual void Update(float deltaTime);
		virtual void FixedUpdate(float deltaTime);
		virtual void Render();

	protected:
		SAppConfig m_config;
		std::unique_ptr<CSysWindow> m_pSysWindow;
		std::unique_ptr<CGraphics> m_pGraphics;
		std::unique_ptr<CResourceManager> m_pResourceManager;
		std::unique_ptr<CSceneManager> m_pSceneManager;
		std::unique_ptr<CInputManager> m_pInputManager;

		double m_prevTime;
		float m_fixedRenderTimer;
		float m_fixedUpdateTimer;
	};
}

