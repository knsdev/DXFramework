#pragma once
#include "stdafx.h"
#include "CSysWindow.h"
#include "SAppConfig.h"
#include "SRenderCommand.h"
#include "EInputLayoutType.h"
#include "CInputLayout.h"
#include "CShader.h"
#include "CResourceManager.h"
#include "CVertexBuffer.h"
#include "CIndexBuffer.h"
#include "CConstantBuffer.h"
#include "SVSConstantBufferData.h"

namespace dxfw
{
	class CInputLayout;
	class CShader;
	class CResourceManager;
	class CVertexBuffer;
	class CIndexBuffer;
	class CConstantBuffer;

	class CGraphics
	{
	public:
		CGraphics(const SAppConfig& config);
		virtual ~CGraphics();

		void SetDependencies(CSysWindow* pSysWindow, CResourceManager* pResourceManager);
		void Init();
		void BeginDraw();
		void EndDraw();

		void AddRenderCommand(const SRenderCommand& command);

		ID3D11Device* GetDevice() { return m_pDevice; }
		ID3D11DeviceContext* GetImmediateContext() { return m_pImmediateContext; }
		IDXGISwapChain* GetSwapChain() { return m_pSwapChain; }

		inline float GetScreenRefreshRate() { return 1.0f / 60.0f; } // TODO: get from adapter

		void SetViewMatrix(const DirectX::XMMATRIX& viewMatrix) { DirectX::XMStoreFloat4x4(&m_viewMatrix, viewMatrix); }
		void SetProjectionMatrix(const DirectX::XMMATRIX& projectionMatrix) { DirectX::XMStoreFloat4x4(&m_projectionMatrix, projectionMatrix); }

	private:
		void LoadResources();
		void InitShadersAndBuffers();
		void UpdateVSConstantBuffer(const DirectX::XMMATRIX& objWorldMatrix);

	private:
		SAppConfig m_config;
		CSysWindow* m_pSysWindow;
		CResourceManager* m_pResourceManager;
		CComPtr<ID3D11Device> m_pDevice;
		CComPtr<ID3D11DeviceContext> m_pImmediateContext;
		CComPtr<IDXGISwapChain> m_pSwapChain;
		CComPtr<ID3D11RenderTargetView> m_pRenderTargetView;
		CComPtr<ID3D11Texture2D> m_pDepthStencilBuffer;
		CComPtr<ID3D11DepthStencilView> m_pDepthStencilView;
		CComPtr<ID3D11DepthStencilState> m_pDepthStencilState;
		CComPtr<ID3D11RasterizerState> m_pRasterizerState;
		CComPtr<ID3D11SamplerState> m_pSamplerState;

		std::vector<SRenderCommand> m_renderCommands;

		std::unique_ptr<CVertexBuffer> m_pVertexBuffer;
		std::unique_ptr<CIndexBuffer> m_pIndexBuffer;

		std::unique_ptr<CConstantBuffer> m_pVSConstantBuffer;

		DirectX::XMFLOAT4X4 m_viewMatrix;
		DirectX::XMFLOAT4X4 m_projectionMatrix;
	};
}
